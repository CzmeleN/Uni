// Jan Mączyński 344907

#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <sys/time.h>
#include <assert.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <poll.h>
#include <stdbool.h>

#define PACKETS_COUNT (3)
#define MAX_TTL (30)
#define TIMEOUT (1000)
#define SEC_MS (1000)
#define USEC_MS (1000)
#define IP_LEN (20)
#define PACKET_SIZE (60)

#define ll long long

// funkcja ze strony wykładu
uint16_t compute_icmp_checksum(const void *buff, int length) {
    const uint16_t* ptr = buff;
    uint32_t sum = 0;

    assert (length % 2 == 0);

    for (; length > 0; length -= 2) sum += *ptr++;

    sum = (sum >> 16U) + (sum & 0xffffU);
    return ~(sum + (sum >> 16U));
}

// funkcja ze strony wykładu
void ERROR(const char *str) {
    fprintf(stderr, "%s: %s\n", str, strerror(errno));  // NOLINT(*-err33-c)
    exit(EXIT_FAILURE);
}

ll get_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);

    return tv.tv_sec * SEC_MS + tv.tv_usec / USEC_MS;
}

void send_req(int fd, pid_t pid, int ttl, struct sockaddr_in *target) {
    for (int i = 0; i < PACKETS_COUNT; ++i) {
        // wrzucenie gołego pakietu hdr nie działa
        uint8_t packet[PACKET_SIZE];
        memset(packet, 0, sizeof(packet));

        struct icmp *hdr = (struct icmp*)packet;
        hdr->icmp_hun.ih_idseq.icd_id = htons(pid);
        hdr->icmp_hun.ih_idseq.icd_seq = htons(ttl * PACKETS_COUNT + i);
        hdr->icmp_type = ICMP_ECHO;
        hdr->icmp_cksum = compute_icmp_checksum(packet, sizeof(packet));

        if (sendto(fd, packet, sizeof(packet), 0, (struct sockaddr*)target,
                   sizeof(*target)) < 0) ERROR("błąd: sendto");
    }
}

bool rec(int fd, pid_t pid, int ttl, ll start) {
    int to_receive = PACKETS_COUNT;
    ll elapsed = 0;
    char ips[PACKETS_COUNT][IP_LEN];
    int uniques = 0;
    bool reached = false;

    while (to_receive) {
        ll curr = get_time();
        ll left = TIMEOUT - curr + start;

        if (left <= 0) break;

        struct pollfd pdf;
        pdf.fd = fd;
        pdf.events = POLLIN;

        int ret = poll(&pdf, 1, left);
        if (ret == 0) break;
        else if (ret < 0) ERROR("błąd: poll");

        // snippet ze strony wykładu
        struct sockaddr_in sender;
        socklen_t sender_len = sizeof(sender);
        uint8_t buff[IP_MAXPACKET];

        ll rect = get_time();

        ssize_t packet_len = recvfrom(fd, buff, IP_MAXPACKET, 0,
                                      (struct sockaddr*)&sender, &sender_len);
        if (packet_len < 0) continue;

        struct ip *ip_hdr = (struct ip*) buff;
        ssize_t ip_hdr_len = 4 * (ssize_t)(ip_hdr->ip_hl);
        struct icmp *icmp_hdr = (struct icmp*)(buff + ip_hdr_len);
        // koniec snippetu

        bool is_valid = false;

        if (icmp_hdr->icmp_type == ICMP_ECHOREPLY) {
            int seq = ntohs(icmp_hdr->icmp_hun.ih_idseq.icd_seq);

            if (ntohs(icmp_hdr->icmp_hun.ih_idseq.icd_id) == pid &&
                seq >= ttl * PACKETS_COUNT && seq < (ttl + 1) * PACKETS_COUNT) {
                is_valid = true;
                reached = true;
            }
        } else if (icmp_hdr->icmp_type == ICMP_TIME_EXCEEDED) {
            struct ip *og_ip = (struct ip*)((uint8_t*)icmp_hdr + 8);
            ssize_t og_ip_hdr_len = 4 * (ssize_t)(og_ip->ip_hl);
            struct icmp *og_icmp = (struct icmp*)((uint8_t*)og_ip + og_ip_hdr_len);

            int seq = ntohs(og_icmp->icmp_hun.ih_idseq.icd_seq);

            if (ntohs(og_icmp->icmp_hun.ih_idseq.icd_id) == pid &&
                seq >= ttl * PACKETS_COUNT && seq < (ttl + 1) * PACKETS_COUNT) is_valid = true;
        }

        if (is_valid) {
            to_receive--;
            elapsed += rect - start;

            char ip[IP_LEN];
            inet_ntop(AF_INET, &(sender.sin_addr), ip, sizeof(ip));

            bool is_unique = true;

            for (int j = 0; j < uniques; ++j) {
                if (strcmp(ips[j], ip) == 0) {
                    is_unique = false;
                    break;
                }
            }

            if (is_unique && uniques < PACKETS_COUNT) strcpy(ips[uniques++], ip);
        }
    }

    printf("%d. ", ttl);

    if (to_receive == PACKETS_COUNT) {
        printf("*\n");
    } else {
        for (int j = 0; j < uniques; ++j) printf("%s ", ips[j]);

        if (to_receive) printf("???\n");
        else printf("%lldms\n", elapsed / PACKETS_COUNT);
    }

    return reached;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "użycie: %s <ip>\n", argv[0]);
        return EXIT_FAILURE;
    }

    struct sockaddr_in target = {0};
    target.sin_family = AF_INET;

    int ret = inet_pton(AF_INET, argv[1], &target.sin_addr);
    if (ret == 0) {
        fprintf(stderr, "błąd: nieprawidłowy adres ip: %s\n", argv[1]);
        return EXIT_FAILURE;
    } else if (ret < 0) {
        ERROR("błąd: inet_pton");
    }

    int fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (fd < 0) ERROR("błąd: socket");

    pid_t pid = getpid();

    for (int i = 1; i < MAX_TTL; ++i) {
        if (setsockopt(fd, IPPROTO_IP, IP_TTL, &i, sizeof(int)) < 0)
            ERROR("błąd: setsockopt");

        ll start = get_time();

        send_req(fd, pid, i, &target);
        if (rec(fd, pid, i, start)) break;
    }

    close(fd);

    return 0;
}
