let ( let* ) xs ys = List.concat_map ys xs

let rec choose m n =
  if m > n then [] else m :: choose (m+1) n

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

let verify_rows pss xss = 
  let rec aux res rows descs =
    match rows with
    | [] -> res
    | row :: rows' -> aux (verify_row row (List.hd descs) && res) rows' (List.tl descs)
  in aux true pss xss

let semi_verify_rows pss xss =
  let rec aux res rows descs =
    match rows with
    | [] -> res
    | row :: rows' -> aux (semi_verify_row row (List.hd descs) && res) rows' (List.tl descs)
  in aux true pss xss

let transpose xss = 
  let rec aux res rows =
    match rows with
    | [] :: _ -> List.rev res
    | rows -> aux ((List.map List.hd rows) :: res) (List.map List.tl rows)
  in aux [] xss

let rec false_list n =
  if n <= 0 then []
  else false :: false_list (n - 1)

let mask_to_list mask n = 
  let rec aux mask =
    let bit = mask mod 2 == 1
  in if mask < 2 then [bit]
    else bit :: aux (mask / 2)
  in let res = aux mask in
    res @ false_list (n - List.length res)

let build_row ps n = 
  let m = 1 lsl n
  in let* mask = choose 0 m
  in let row = mask_to_list mask n
  in if verify_row ps row then [row] else []

let list_product xss ys = 
  let* tl = xss
  in let* hd = ys
  in [hd::tl]

(*funkcje pozwalające rozłączyć opisy wierszy i kolumn przekazane jako jedna dłuższa lista
   (żeby zgadzały się ze specyfikacją funkcji na WEB-CAT*)

let rec take n xs =
  match n, xs with
  | 0, _ -> []
  | _, [] -> []
  | n, x :: xs' -> x :: take (n - 1) xs'

let rec drop n xs =
  match n, xs with
  | 0, _ -> xs
  | _, [] -> []
  | n, _ :: xs' -> drop (n - 1) xs'

let build_candidate pss n = 
  let row_descs = take n pss
  and col_descs = drop n pss
  in let rec generator res row_descs =
    match row_descs with
    | [] -> List.map List.rev res
    | row_desc::row_descs' -> let new_rows = list_product res (build_row row_desc n)
      in let filtered_new_rows = new_rows
      |> List.filter (fun xss -> xss |> List.rev |> transpose |> semi_verify_rows col_descs)
      in generator filtered_new_rows row_descs'
  in generator [[]] row_descs

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

let big_example = {
  rows = [[1;2];[2];[1];[1];[2];[2;4];[2;6];[8];[1;1];[2;2]];
  cols = [[2];[3];[1];[2;1];[5];[4];[1;4;1];[1;5];[2;2];[2;1]]
}