type source =
  | InterestingNumber(string, InterestingNumber.t)
  | Achievement(Achievement.t)
  | CelestialDuration(CelestialDuration.t);

type t = {
  date: Js.Date.t,
  source,
};

open Iterator;

let makeDateAdder = ((singularUnit, pluralUnit, adder), date, number) => {
  date: adder(number.InterestingNumber.value, date),
  source:
    InterestingNumber(
      Utils.pluralize(singularUnit, pluralUnit, number.value),
      number,
    ),
};

let interestingNumbers = (birthday, maxDate) => {
  let pairs = InterestingNumber.pairs;
  pairs
  |> map(((generator, dateAdder)) => {
       let addToDate = dateAdder |> makeDateAdder;
       generator()
       |> map(number => addToDate(birthday, number))
       |> takeWhile(ann => ann.date |> DateFns.isBefore(maxDate))
       |> toList;
     })
  |> toList;
};

let achievements = (birthday, _maxDate) =>
  Achievement.achievements
  |> List.map((achievement: Achievement.t) => {
       let difference =
         DateFns.differenceInCalendarDays(
           achievement.date,
           achievement.birthday,
         );
       let date = DateFns.addDays(difference, birthday);
       {date, source: Achievement(achievement)};
     });

let celestialDurations = (birthday, maxDate) =>
  CelestialDuration.celestialDurations(birthday, maxDate)
  |> List.map((celestialDuration: CelestialDuration.t) =>
       (
         {
           date: celestialDuration.date,
           source: CelestialDuration(celestialDuration),
         }: t
       )
     );