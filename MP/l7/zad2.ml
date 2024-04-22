(* for loop z pascala *)

type expr = 
  | Int of int
  | Var of string
  | Seq of expr list
  | ForLoop of string * expr * expr * expr

(* w for i := n to m do ... end (* pętla w Pascalu *) i - string, n - var, m - var, reszta - seq list *)

(* całka *)

type expr = 
  | Int of int
  | Var of string
  | Fun of string * expr
  | Integral of expr * expr * expr * string (* dać np dx *)

(* w n, k integral f(x) dx // n - var, k - var, f(x) - fun, dx - string *)