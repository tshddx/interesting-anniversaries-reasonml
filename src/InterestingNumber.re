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

let repeated_digits = () => {
  let nums = ref([]);
  for (exponent in 3 to 10) {
    let power_of_ten = 10.0 ** float_of_int(exponent);
    let all_ones = (power_of_ten -. 1.0) /. 9.0;
    for (digit in 1 to 9) {
      let value = float_of_int(digit) *. all_ones;
      let number = {category: "repeated_digits", value, description: None};
      let n = nums^;
      nums := [number, ...n];
    };
  };
  nums^;
};

let counting_up = () => {
  let nums = ref([]);
  for (exponent in 5 to 10) {
    let power_of_ten = 10.0 ** float_of_int(exponent);
    let value = floor(137174210.0 /. 1111111111.0 *. power_of_ten);
    let number = {category: "counting_up", value, description: None};
    let n = nums^;
    nums := [number, ...n];
  };
  nums^;
};

let generators = [
  powers_of_ten,
  powers_of_two,
  factors_of_ten,
  repeated_digits,
  counting_up,
];