type source =
  | InterestingNumber(string, InterestingNumber.t)
  | Achievement(Achievement.t);

type t = {
  date: Js.Date.t,
  source,
};

open Iterator;

let makeDateAdder = ((unit, adder), date, number) => {
  date: adder(number.InterestingNumber.value, date),
  source: InterestingNumber(unit, number),
};

let interestingNumbers = (birthday, maxDate) => {
  let numberGenerators = InterestingNumber.numberGenerators |> fromList;
  let dateAdders =
    InterestingNumber.dateAdders |> List.map(makeDateAdder) |> fromList;
  let pairs = product(numberGenerators, dateAdders);
  pairs
  |> map(((generator, addToDate)) =>
       generator()
       |> map(number => addToDate(birthday, number))
       |> takeWhile(ann => ann.date |> DateFns.isBefore(maxDate))
       |> toList
     )
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