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
    "Iterator",
    ExpectJs.(
      () =>
        describe("combinations2", () =>
          test("works", () => {
            let iter = combinations2(range(1, 3));
            let combinations = iter |> toList;
            let expected = [(1, 2), (1, 3), (2, 3)];
            expect(combinations) |> toEqual(expected);
          })
        )
    ),
  );