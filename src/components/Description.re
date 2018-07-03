let component = ReasonReact.statelessComponent("Description");

let s = ReasonReact.string;

let make = (~anniversary: Anniversary.t, ~isPast, ~isToday, _children) => {
  ...component,
  render: _self => {
    let date = anniversary.date |> Utils.df;
    let youWere = isPast ? " you were " : " you will be ";
    let todayYouAre = isToday ? "Today you are" : {j|On $date $youWere |j};
    let todayYouTurn = isToday ? "Today you turn" : {j|On $date $youWere |j};
    let description =
      switch (anniversary.source) {
      | InterestingNumber(unit, number) =>
        let n = CommaNumber.commaNumber(number.value);
        let description =
          switch (number.description) {
          | Some(description) => {j|($description) |j}
          | None => ""
          };
        <span>
          (s({j|$todayYouTurn |j}))
          <b> (s({j|$n $(description)$unit|j})) </b>
          (s(" old!"))
        </span>;
      | Achievement(achievement) =>
        <span>
          (s({j|$todayYouAre the same age as |j}))
          <b> (s(achievement.name)) </b>
          (s(" when "))
          (s(achievement.achievement))
          (s("!"))
        </span>
      | CelestialDuration(celestialDuration) =>
        let n = string_of_int(celestialDuration.number);
        let years =
          Utils.pluralize(
            "year",
            "years",
            float_of_int(celestialDuration.number),
          );
        <span>
          (s({j|$todayYouTurn $n $years old in |j}))
          <b> (s(celestialDuration.name)) </b>
          (s(" years!"))
        </span>;
      };
    description;
  },
};

let text = (anniversary: Anniversary.t, isPast, isToday) => {
  let date = anniversary.date |> Utils.df;
  let iWas = isPast ? "I was" : "I will be";
  let iTurn = isPast ? "I turned" : "I will turn";
  let todayIAm = isToday ? "Today I am" : {j|On $date $iWas|j};
  let todayITurn = isToday ? "Today I turn" : {j|On $date $iTurn|j};
  let description =
    switch (anniversary.source) {
    | InterestingNumber(unit, number) =>
      let n = CommaNumber.commaNumber(number.value);
      let description =
        switch (number.description) {
        | Some(description) => {j|($description) |j}
        | None => ""
        };
      {j|$todayITurn $n $(description)$unit old!|j};
    | Achievement({name, achievement}) => {j|$todayIAm the same age as $name when $(achievement)!|j}
    | CelestialDuration({name, number}) =>
      let n = string_of_int(number);
      let years = Utils.pluralize("year", "years", float_of_int(number));
      {j|$todayITurn $n $years old in $name years!|j};
    };
  description;
};