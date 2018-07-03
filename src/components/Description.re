let component = ReasonReact.statelessComponent("Description");

let make = (~anniversary: Anniversary.t, ~isPast, ~isToday, _children) => {
  ...component,
  render: _self => {
    let date = anniversary.date |> Utils.df;
    let description =
      switch (anniversary.source) {
      | InterestingNumber(unit, number) =>
        <span>
          (ReasonReact.string("On "))
          (ReasonReact.string(date))
          (ReasonReact.string(isPast ? " you were " : " you will be "))
          <b>
            (ReasonReact.string(CommaNumber.commaNumber(number.value)))
            (ReasonReact.string(" "))
            (
              ReasonReact.string(
                switch (number.description) {
                | Some(description) => {j|($description) |j}
                | None => ""
                },
              )
            )
            (ReasonReact.string(unit))
          </b>
          (ReasonReact.string(" old!"))
        </span>
      | Achievement(achievement) =>
        <span>
          (ReasonReact.string({|On |}))
          (ReasonReact.string(date))
          (
            ReasonReact.string(
              isPast ?
                " you were the same age as " : " you will be the same age as ",
            )
          )
          <b> (ReasonReact.string(achievement.name)) </b>
          (ReasonReact.string(" when "))
          (ReasonReact.string(achievement.achievement))
          (ReasonReact.string("!"))
        </span>
      | CelestialDuration(celestialDuration) =>
        <span>
          (ReasonReact.string({|On |}))
          (ReasonReact.string(date))
          (ReasonReact.string(isPast ? " you were " : " you will be "))
          (ReasonReact.string(string_of_int(celestialDuration.number)))
          (ReasonReact.string(" "))
          (
            ReasonReact.string(
              Utils.pluralize(
                "year",
                "years",
                float_of_int(celestialDuration.number),
              ),
            )
          )
          (ReasonReact.string(" old in "))
          <b> (ReasonReact.string(celestialDuration.name)) </b>
          (ReasonReact.string(" years!"))
          (ReasonReact.string("!"))
        </span>
      };
    description;
  },
};