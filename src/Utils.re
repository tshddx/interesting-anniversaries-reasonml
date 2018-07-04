let floatToInt = f => f |> Int32.of_float |> Int32.to_int;

let intToFloat = i => i |> Int32.of_int |> Int32.to_float;

let exp = (base, exponent) =>
  intToFloat(base) ** intToFloat(exponent) |> floatToInt;

let round = n => n > 0.0 ? floor(n +. 0.5) : ceil(n -. 0.5);

let df = date => DateFns.format("MMMM D, YYYY", date);

let listAssoc = (key, l) =>
  switch (List.assoc(key, l)) {
  | value => Some(value)
  | exception Not_found => None
  };

let listFind = (predicate, l) =>
  switch (List.find(predicate, l)) {
  | value => Some(value)
  | exception Not_found => None
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

let optionGet = option =>
  switch (option) {
  | Some(value) => value
  | None => raise(Not_found)
  };

let pluralize = (singular, plural, count) =>
  if (count === 1.0) {
    singular;
  } else {
    plural;
  };

let integerWords = [
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

let exponentWords = [
  (2, "hundred"),
  (3, "thousand"),
  (6, "million"),
  (9, "billion"),
  (12, "trillion"),
];

let tenTo = exponent => 10.0 ** float_of_int(exponent);

let ranges = [
  /* (tenTo(2), tenTo(3), "hundred"), */
  (tenTo(3), tenTo(6), "thousand"),
  (tenTo(6), tenTo(9), "million"),
  (tenTo(9), tenTo(12), "billion"),
  (tenTo(12), tenTo(15), "trillion"),
];

let numberInWords2 = number => {
  let range =
    ranges |> listFind(((min, max, _word)) => min <= number && number < max);
  switch (range) {
  | Some((min, _max, unit)) =>
    let significand = number /. min;
    let significandFloor = floor(significand);
    if (significand == significandFloor) {
      let significandInt = int_of_float(significand);
      let significandWord =
        integerWords
        |> listAssoc(significandInt)
        |> optionDefault(string_of_int(significandInt));
      {j|$significandWord $unit|j};
    } else {
      CommaNumber.commaNumber(number);
    };
  | None => CommaNumber.commaNumber(number)
  };
};

let numberInWords = number => {
  /* Think of `number` in scientific notation:
     number = significand * 10^exponent
     `significand` gives us the first word ("one", "two", etc.)
     `exponent` gives us the second word ("hundred", "thousand", etc.)
     */
  let number = floor(number);
  let exponent = number |> log10 |> floor;
  let significand = number /. 10.0 ** exponent |> floor;
  Js.log3(number, significand, exponent);
  if (significand *. 10.0 ** exponent != number) {
    CommaNumber.commaNumber(number);
  } else {
    let significandWord =
      integerWords
      |> listAssoc(significand |> int_of_float)
      |> optionDefault(significand |> int_of_float |> string_of_int);
    let exponentWord = exponentWords |> listAssoc(exponent |> int_of_float);
    Js.log2(significandWord, exponentWord);
    switch (exponentWord) {
    | Some(exponentWord) => {j|$significandWord $exponentWord|j}
    | _ => CommaNumber.commaNumber(number)
    };
  };
};