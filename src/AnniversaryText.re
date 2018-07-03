let intro = (anniversary: Anniversary.t, isPast: bool, isToday: bool) => {
  let date = anniversary.date |> Utils.df;
  let first = isToday ? "Today" : {j|On $date|j};
  let verb = isToday ? "am" : isPast ? "was" : "will be";
  {j|$first, I $verb|j};
};

let sentence = (anniversary: Anniversary.t, isPast: bool, isToday: bool) => {
  let iWillBe = intro(anniversary, isPast, isToday);
  switch (anniversary.source) {
  | InterestingNumber(unit, number) =>
    let num = CommaNumber.commaNumber(number.value);
    let description =
      switch (number.description) {
      | Some(desc) => {j|($desc) |j}
      | None => ""
      };
    {j|$iWillBe $num $description$unit old!|j};
  | Achievement(achievement) =>
    let name = achievement.name;
    let achievement = achievement.achievement;
    {j|$iWillBe the same age as $name when $achievement!|j};
  | CelestialDuration(celestialDuration) =>
    let num = string_of_int(celestialDuration.number);
    let name = celestialDuration.name;
    {j|$iWillBe $num years old in $name years!|j};
  };
};