from random import randint as ri

#08:55:36 192.168.0.1 GET /TheApplication/WebResource.axd 200

ip_list = [f"{ri(0, 255)}.{ri(0,255)}.{ri(0,255)}.{ri(0,255)}" for i in range(200)]

for h in range(24):
    for m in range(60):
        for s in range(60):
            print(f"{h:02}:{m:02}:{s:02} {ip_list[ri(0,199)]} GET /TheApplication/WebResource.axd 200")

