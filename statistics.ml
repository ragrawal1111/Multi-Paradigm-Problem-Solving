(* 
 * Assignment 7: Multi-Paradigm Problem Solving
 * OCaml Implementation - Functional Approach
 *
 * Calculates mean, median, and mode of a list of integers.
 * Uses immutable data and higher-order functions (map, fold, filter).
 *)

(* Calculate the mean using List.fold_left to sum all elements *)
let calculate_mean lst =
  let n = List.length lst in
  let sum = List.fold_left (fun acc x -> acc + x) 0 lst in
  float_of_int sum /. float_of_int n

(* Calculate the median by sorting and picking the middle element(s) *)
let calculate_median lst =
  let sorted = List.sort compare lst in
  let n = List.length sorted in
  if n mod 2 = 1 then
    float_of_int (List.nth sorted (n / 2))
  else
    let lower = List.nth sorted (n / 2 - 1) in
    let upper = List.nth sorted (n / 2) in
    float_of_int (lower + upper) /. 2.0

(* Build a frequency map using fold, then filter for maximum frequency *)
let calculate_mode lst =
  (* Build frequency map: list of (value, count) pairs using fold_left *)
  let freq_map =
    List.fold_left
      (fun acc x ->
        if List.mem_assoc x acc then
          List.map (fun (k, v) -> if k = x then (k, v + 1) else (k, v)) acc
        else
          (x, 1) :: acc)
      [] lst
  in
  (* Find the maximum frequency using fold_left *)
  let max_freq =
    List.fold_left (fun acc (_, count) -> max acc count) 0 freq_map
  in
  (* Filter to get all elements that have the maximum frequency *)
  let modes =
    List.map fst (List.filter (fun (_, count) -> count = max_freq) freq_map)
  in
  let modes_sorted = List.sort compare modes in
  (modes_sorted, max_freq)

(* Helper to convert an int list to a string representation *)
let string_of_int_list lst =
  "[" ^ String.concat ", " (List.map string_of_int lst) ^ "]"

(* Display statistics for a given dataset *)
let display_statistics label data =
  Printf.printf "=== Statistics Calculator (OCaml - Functional) %s===\n\n" label;
  Printf.printf "Input data: %s\n" (string_of_int_list data);
  Printf.printf "Number of elements: %d\n\n" (List.length data);

  let sorted = List.sort compare data in
  Printf.printf "Sorted data: %s\n\n" (string_of_int_list sorted);

  let mean = calculate_mean data in
  let median = calculate_median data in
  let (modes, freq) = calculate_mode data in

  Printf.printf "--- Results ---\n";
  Printf.printf "Mean:   %.2f\n" mean;
  Printf.printf "Median: %.2f\n" median;
  if freq = 1 then
    Printf.printf "Mode:   No mode (all values appear once)\n"
  else
    Printf.printf "Mode:   %s (each appears %d times)\n"
      (string_of_int_list modes) freq

(* Main entry point *)
let () =
  (* First dataset *)
  let data1 = [4; 7; 2; 9; 1; 5; 7; 3; 7; 2; 8; 6; 5; 3; 7] in
  display_statistics "" data1;

  Printf.printf "\n========================================\n\n";

  (* Second dataset with multiple modes *)
  let data2 = [10; 20; 20; 30; 30; 40; 50] in
  display_statistics "" data2
