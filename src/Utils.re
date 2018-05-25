let floatToInt = f => f |> Int32.of_float |> Int32.to_int;

let intToFloat = i => i |> Int32.of_int |> Int32.to_float;

let exp = (base, exponent) =>
  intToFloat(base) ** intToFloat(exponent) |> floatToInt;

let df = date => DateFns.format("MMMM D, YYYY", date);