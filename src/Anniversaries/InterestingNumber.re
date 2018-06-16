type t = {
  category: string,
  value: float,
  description: option(string),
};

open Iterator;

/* These are sequences of floats. Most of them are infinite sequences. */
let powersOfTen = (start, ()) =>
  count(start) |> map(float_of_int) |> map(f => 10.0 ** f);

let factorsOfTen = () =>
  powersOfTen(0, ())
  |> mapIter(i => just(2.0 *. i) |> andThen(() => just(5.0 *. i)));

let repeatedDigits = () =>
  powersOfTen(3, ())
  |> map(pow => (pow -. 1.0) /. 9.0)
  |> mapIter(all_ones =>
       range(1, 9) |> map(digit => float_of_int(digit) *. all_ones)
     );

let countingUp = () =>
  powersOfTen(5, ()) |> map(pow => floor(137174210.0 /. 1111111111.0 *. pow));

let makeNumberGenerator = (category, generator, ()) =>
  generator() |> map(f => {category, value: f, description: None});

let numberGenerators: list(generator(t)) = [
  powersOfTen(0) |> makeNumberGenerator("powersOfTen"),
  factorsOfTen |> makeNumberGenerator("factorsOfTen"),
  repeatedDigits |> makeNumberGenerator("repeatedDigits"),
  countingUp |> makeNumberGenerator("countingUp"),
];

/* These are simple calculators that add units of time to a date. */
let seconds = ("seconds", DateFns.addSeconds);

let minutes = ("minutes", DateFns.addMinutes);

let hours = ("hours", DateFns.addHours);

let days = ("days", DateFns.addDays);

let weeks = ("weeks", DateFns.addWeeks);

let months = ("months", DateFns.addMonths);

let years = ("years", DateFns.addYears);

let dateAdders = [seconds, minutes, hours, days, weeks, months, years];