type number = {
  category: string,
  value: int,
};

open Iterator;

let powers_of_ten = () =>
  count(0)
  |> map(i => Utils.exp(10, i))
  |> map(i => {category: "powers_of_ten", value: i});

let powers_of_two = () =>
  count(0)
  |> map(i => Utils.exp(2, i))
  |> map(i => {category: "powers_of_two", value: i});

List.iter(
  iterable =>
    iterable() |> take_while(({value}) => value < 5000) |> each(Js.log),
  [powers_of_ten, powers_of_two],
);