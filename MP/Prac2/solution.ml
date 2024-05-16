(* abstract syntax tree *)

type bop = Mult | Div | Add | Sub | Eq | Lt | Gt | Leq | Geq | Neq

type ident = string

type expr =
  | Int of int
  | Bool of bool
  | Binop of bop * expr * expr
  | If of expr * expr * expr
  | Var of ident
  | Let of ident * expr * expr

(* Własny kod *)

(* Kod z zadania 2. z listy 8. do alpha-equiv sposobem 2. *)
let rec index_of predicate list : int =
  let rec aux index = function
    | [] -> raise Not_found
    | head :: tail -> if predicate head then index else aux (index + 1) tail
  in
  aux 0 list
 
let rec to_debruijn (expr : expr) (env : ident list) : expr =
  match expr with
  | Int value -> Int value
  | Bool bool_value -> Bool bool_value
  | Binop (oper, expr1, expr2) ->
    Binop (oper, to_debruijn expr1 env, to_debruijn expr2 env)
  | If (cond, true_branch, false_branch) ->
    If (to_debruijn cond env, to_debruijn true_branch env, to_debruijn false_branch env)
  | Var var ->
    (try Var (string_of_int (index_of (fun env_var -> env_var = var) env))
     with Not_found -> Var var)
  | Let (var, binding_expr, body_expr) ->
    Let ("", to_debruijn binding_expr env, to_debruijn body_expr (var :: env))
 
let alpha_equiv (expr1 : expr) (expr2 : expr) : bool =
  let db_expr1 = to_debruijn expr1 []
  and db_expr2 = to_debruijn expr2 [] in
  db_expr1 = db_expr2

(* Zwraca listę zmiennych wolnych w wyrażeniu - 
   zagłębiając się dodaje zmienne do listy a gdy napotka 
   let odfiltrowuje te zmienną od tych które pojawiły się głębiej *)
let rec free_vars (expr : expr) : ident list =
  match expr with
  | Int _ | Bool _ -> []
  | Var x -> [x]
  | Binop (_, e1, e2) -> 
      free_vars e1 @ free_vars e2
  | If (e1, e2, e3) -> 
      free_vars e1 @ free_vars e2 @ free_vars e3
  | Let (x, e1, e2) -> 
      free_vars e1 @ List.filter (fun y -> y <> x) (free_vars e2)

(* Generuje wszystkie podwyrażenia które są nietrywialne *)
let rec sub_exprs (expr : expr) : expr list =
  match expr with
  | Int _ | Bool _ | Var _ -> []
  | Binop (_, e1, e2) ->
      expr :: (sub_exprs e1 @ sub_exprs e2)
  | If (e1, e2, e3) ->
      expr :: (sub_exprs e1 @ sub_exprs e2 @ sub_exprs e3)
  | Let (_, e1, e2) ->
      expr :: (sub_exprs e1 @ sub_exprs e2)

(* Sprawdza czy dwa wyrażenia są równoważne wg zasad z treści *)
let equiv (e1 : expr) (e2 : expr) (free_vs : ident list) : bool =
  alpha_equiv e1 e2 &&
  List.for_all (fun x -> List.mem x free_vs) (free_vars e1) &&
  List.for_all (fun x -> List.mem x free_vs) (free_vars e2)

(* Czy podwyrażenie ma inne równoważne w wyrażeniu *)
let has_equiv (sub_ex : expr) (expr : expr) : bool =
  let rec aux ex free_vars_expr subexpressions_expr count =
    match subexpressions_expr with
    | [] -> count > 1
    | x :: tl -> if equiv sub_ex x free_vars_expr
      then aux ex free_vars_expr tl (count + 1)
      else aux ex free_vars_expr tl count
  in aux sub_ex (free_vars expr) (sub_exprs expr) 0

(* Sprawdza czy wyrażenie znajduje się w liście *)
let rec is_in (expr : expr) (expr_list : expr list) (free_vs : ident list) : bool =
  match expr_list with
  | [] -> false
  | x :: tl -> if equiv expr x free_vs
    then true
    else is_in expr tl free_vs

(* Zwraca listę wyrażeń których równoważne trzeba zastąpić *)
let subs_to_replace (expr : expr) : expr list =
  let free_vs = free_vars expr in
  let all_subexprs = sub_exprs expr in
  let rec find_duplicates acc all_subexprs =
    match all_subexprs with
    | [] -> acc
    | x :: tl -> if has_equiv x expr && not (is_in x acc free_vs)
      then find_duplicates (x :: acc) tl
      else find_duplicates acc tl
  in find_duplicates [] all_subexprs

(* Zastąpienie podwyrażeń -
   każdego równoważnego zastępującemu *)
let replace (new_var : expr) (to_replace : expr) (expr : expr) : expr =
  let free_vs = free_vars expr in
  let rec aux new_var to_replace expr org_expr =
    if equiv expr to_replace free_vs then
      new_var
    else
      match expr with
      | Binop (op, e1, e2) -> Binop (op, aux new_var to_replace e1 org_expr, aux new_var to_replace e2 org_expr)
      | If (e1, e2, e3) -> If (aux new_var to_replace e1 org_expr, aux new_var to_replace e2 org_expr, aux new_var to_replace e3 org_expr)
      | Let (x, e1, e2) -> Let (x, aux new_var to_replace e1 org_expr, aux new_var to_replace e2 org_expr)
      | _ -> expr in
  aux new_var to_replace expr expr

(* Optymalizacja wspólnych podwyrażeń -
   tylko jednej grupy (jak w treści) *)
let cse (expr : expr) : expr option =
  let to_replace = subs_to_replace expr in
  let rec aux expr to_replace =
    match to_replace with
    | [] -> None
    | x :: _ ->
      Some (Let ("tmp", x, replace (Var "tmp") x expr)) in
  aux expr to_replace