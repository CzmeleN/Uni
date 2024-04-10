let ( let* ) xs ys = List.concat_map ys xs

let rec choose m n =
  if m > n then [] else m :: choose (m+1) n
(*powyżej ze wzorca*)

(*sprawdzenie poprawności wiersza, rozpatruje każdy przypadek ręcznie
   śledząc długość aktualnego bloku jedynek, zwraca fałsz m.in.
   gdy przekroczymy tą długość, skończymy blok za wcześnie lub
   skończymy wiersz nie przechodząc wszystkich bloków*)
let verify_row (ps : int list) (xs : bool list) = 
  let rec aux row desc curr =
    match row, desc with
    | [], [] -> true
    | [], [block] -> curr == block
    | [], _ -> false
    | true :: row', [] -> false
    | true :: row', block :: desc' ->
      if block == curr then false
      else aux row' desc (curr + 1)
    | false :: row', [] -> aux row' desc 0
    | false :: row', block :: desc' ->
        if curr == 0 then aux row' desc 0 else
        if curr == block then aux row' desc' 0
        else false
  in aux xs ps 0

(*podobnie jak wyżej, natomiast zwraca prawdę także w przypadku
   niedokończonych wierszy, które mają szansę okazać się poprawne
   przy przeszukiwaniu kolejnych stanów*)
let semi_verify_row ps xs =
  let rec aux row desc curr =
    match row, desc with
    | [], _ -> true
    | true :: row', [] -> false
    | true :: row', block :: desc' ->
      if curr == block then false
      else aux row' desc (curr + 1)
    | false :: row', [] -> aux row' desc 0
    | false :: row', block :: desc' ->
      if curr == 0 then aux row' desc 0
      else aux row' (if curr == block then desc' else []) 0
  in aux xs ps 0

(*sprawdza po kolei wiersze korzystając z funkcji powyżej,
   przechodzi do końca lub kończy na pierwszym fałszu*)
let verify_rows pss xss = 
  let rec aux rows descs =
    match rows with
    | [] -> true
    | row :: rows' ->
      if verify_row (List.hd rows) (List.hd descs)
      then aux rows' (List.tl descs)
      else false
  in aux pss xss

(*podobnie jak wyżej, z inną funkcją*)
let semi_verify_rows pss xss = 
  let rec aux rows descs =
    match rows with
    | [] -> true
    | row :: rows' ->
      if semi_verify_row (List.hd rows) (List.hd descs)
      then aux rows' (List.tl descs)
      else false
  in aux pss xss

(*pierwszy nawias przy rows -> aux pobiera pierwsze elementy z każdego wiersza
   i dodaje do wyniku, a potem wykonujemy funkcję na liście list
   bez pierwszym elementów i wykonujemy to samo,
   zamieniając wszystkie wiersze na kolumny*)
let transpose xss = 
  let rec aux res rows =
    match rows with
    | [] :: _ -> List.rev res
    | rows -> aux ((List.map List.hd rows) :: res) (List.map List.tl rows)
  in aux [] xss

(*generowanie listy fałszów*)
let rec false_list n =
  if n <= 0 then []
  else false :: false_list (n - 1)

(*bitowy zapis na postać listy T/F (odwrócony,
   nie robi to dla nas różnicy)*)
let mask_to_list mask n = 
  let rec aux mask =
    let bit = mask mod 2 == 1
  in if mask < 2 then [bit]
    else bit :: aux (mask / 2)
  in let res = aux mask in
    res @ false_list (n - List.length res)

(*generowanie wszystkich możliwych kombinacji jedynek i zer jako
   maski bitowe i odrzucanie niepoprawnych kombinacji, jest to łatwiejszy
   w napisaniu niż generowanie rekurencyjnie bloków na wszystkich pozycjach,
   shift w lewo to oczywiście 2^n*)
let build_row ps n = 
  let m = 1 lsl n
  in let* mask = choose 0 m
  in let row = mask_to_list mask n
  in if verify_row ps row then [row] else []

(*tworzenie produktu kartezjańskiego dwóch list, łącząc każdy element
   z ys z każdą podlistą xss*)
let list_product xss ys = 
  let* tl = xss
  in let* hd = ys
  in [hd::tl]

(*funkcje pozwalające rozłączyć opisy wierszy i kolumn przekazane jako jedna dłuższa lista
   (żeby zgadzały się ze specyfikacją funkcji na WEB-CAT*)
let rec first n xs =
  match n, xs with
  | 0, _ -> []
  | _, [] -> []
  | n, x :: xs' -> x :: first (n - 1) xs'

let rec last n xs =
  List.rev (first n (List.rev xs))

(*przyjmujemy opisy wierszy i kolumn aby móc eliminować wcześnie niepoprawne wiersze po kolumnach,
   pozwala nam to na wygenerowanie relatywnie mało ostatecznych stanów, w skrócie bierzemy obecną listę
   kandydatów res i sprawdzamy z każdą możliwością nowego wiersza czy zgadza się po kolumnach
   przy pomocy funkcji transpose i filtrowaniu listy funkcją semi_verify która sprawdza czy istnieje
   szansa na dokończenie tych kolumn, i dalej wywołujemy tę funkcję z listą dłuższych list wierszy*)  
let build_candidate pss n = 
  let row_descs = first ((List.length pss) - n) pss
  and col_descs = last n pss
  in let rec aux res row_descs =
    match row_descs with
    | [] -> List.map List.rev res
    | row_desc :: row_descs' -> let new_rows = list_product res (build_row row_desc n)
      in let filtered_new_rows = new_rows
      |> List.filter (fun xss -> xss |> List.rev |> transpose |> semi_verify_rows col_descs)
      in aux filtered_new_rows row_descs'
  in aux [[]] row_descs

(*poniżej ze wzorca*)
type nonogram_spec = {rows: int list list; cols: int list list}

let solve_nonogram nono =
  build_candidate (nono.rows @ nono.cols) (List.length (nono.cols))
  |> List.filter (fun xss -> transpose xss |> verify_rows nono.cols)

let example_1 = {
  rows = [[2];[1];[1]];
  cols = [[1;1];[2]]
}

let example_2 = {
  rows = [[2];[2;1];[1;1];[2]];
  cols = [[2];[2;1];[1;1];[2]]
}

let example_3 = {
  rows = [[3];[0];[1]];
  cols = [[1];[1];[1;1]]
}

let big_example = {
  rows = [[1;2];[2];[1];[1];[2];[2;4];[2;6];[8];[1;1];[2;2]];
  cols = [[2];[3];[1];[2;1];[5];[4];[1;4;1];[1;5];[2;2];[2;1]]
}