let floatToInt = f => f |> Int32.of_float |> Int32.to_int;

let intToFloat = i => i |> Int32.of_int |> Int32.to_float;

let exp = (base, exponent) =>
  intToFloat(base) ** intToFloat(exponent) |> floatToInt;

let df = date => DateFns.format("MMMM D, YYYY", date);

let integers = [
  (1, "one"),
  (2, "two"),
  (3, "three"),
  (4, "four"),
  (5, "five"),
  (6, "six"),
  (7, "seven"),
  (8, "eight"),
  (9, "nine"),
];

let exponents = [
  (100, "hundred"),
  (1_000, "thousand"),
  (1_000_000, "million"),
  (1_000_000, "billion"),
  (1_000_000_000, "trillion"),
];

let numberInWords = number => {
  /* Think of `number` in scientific notation:
     number = significand * 10^exponent
     `significand` gives us the first word ("one", "two", etc.)
     `exponent` gives us the second word ("hundred", "thousand", etc.)
     */
  let float = float_of_int(number);
  let exponent = float |> log10 |> floor;
  let significand = float /. 10.0 ** exponent;
  let exponentWord = exponents |> List.assoc(exponent |> int_of_float);
  let significandWord = integers |> List.assoc(significand |> int_of_float);
  ();
};

let optionMap = (mapper, option) =>
  switch (option) {
  | Some(value) => Some(mapper(value))
  | None => None
  };

let optionDefault = (default, option) =>
  switch (option) {
  | Some(value) => value
  | None => default
  };

let pluralize = (singular, plural, count) =>
  if (count === 1.0) {
    singular;
  } else {
    plural;
  };