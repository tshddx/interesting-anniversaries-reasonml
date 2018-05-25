type t = {
  category: string,
  value: float,
  description: option(string),
};

type generator = unit => list(t);

let count = length => {
  let nums = ref([]);
  for (i in length downto 0) {
    let n = nums^;
    nums := [Int32.of_int(i), ...n];
  };
  nums^;
};

let powers_of_ten_helper = length =>
  List.map(
    i => {
      category: "powers_of_ten",
      value: 10.0 ** Int32.to_float(i),
      description: None,
    },
    count(length),
  );

let powers_of_ten = () => powers_of_ten_helper(12);

let powers_of_two = () =>
  List.map(
    i => {
      let value = 2.0 ** Int32.to_float(i);
      {category: "powers_of_two", value, description: Some({j|2^$i|j})};
    },
    count(33),
  );

let factors_of_ten = () =>
  List.map(
    ({value}) => [
      {category: "factors_of_ten", value: value *. 2.0, description: None},
      {category: "factors_of_ten", value: value *. 5.0, description: None},
    ],
    powers_of_ten(),
  )
  |> List.flatten;

let generators = [powers_of_ten, powers_of_two, factors_of_ten];