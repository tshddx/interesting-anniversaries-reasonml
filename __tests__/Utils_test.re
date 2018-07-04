open Jest;

open Utils;

open Iterator;

let roundedNumbers = [
  (0.0, 0.0),
  (0.1, 0.0),
  (0.499999999999999, 0.0),
  (0.5, 1.0),
  (0.5, 1.0),
  (0.9, 1.0),
];

let foo =
  describe(
    "Utils",
    ExpectJs.(
      () =>
        describe("round", () =>
          roundedNumbers
          |> List.iter(((a, b)) => {
               test({j|round($a) == $b|j}, () =>
                 expect(round(a) == b) |> toBeTruthy
               );
               test({j|round(-$a) == -$b|j}, () =>
                 expect(-. round(a) == -. b) |> toBeTruthy
               );
             })
        )
    ),
  );