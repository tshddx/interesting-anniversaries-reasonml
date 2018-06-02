type t = {
  category: string,
  value: float,
  description: option(string),
};

open Iterator;

let powers_of_ten = (start, ()) =>
  count(start) |> map(float_of_int) |> map(f => 10.0 ** f);

let factors_of_ten = () =>
  powers_of_ten(0, ())
  |> map_iter(i => just(2.0 *. i) |> and_then(() => just(5.0 *. i)));

let repeated_digits = () =>
  powers_of_ten(3, ())
  |> map(pow => (pow -. 1.0) /. 9.0)
  |> map_iter(all_ones =>
       range(1, 9) |> map(digit => float_of_int(digit) *. all_ones)
     );

let counting_up = () =>
  powers_of_ten(5, ())
  |> map(pow => floor(137174210.0 /. 1111111111.0 *. pow));

let make_generator = (category, generator, ()) =>
  generator() |> map(f => {category, value: f, description: None});

let generators: list(generator(t)) = [
  powers_of_ten(0) |> make_generator("powers_of_ten"),
  factors_of_ten |> make_generator("factors_of_ten"),
  repeated_digits |> make_generator("repeated_digits"),
  counting_up |> make_generator("counting_up"),
];