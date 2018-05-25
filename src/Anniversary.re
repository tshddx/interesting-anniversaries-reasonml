type achievement = {
  name: string,
  achievement: string,
  birthday: Js.Date.t,
  date: Js.Date.t,
};

type source =
  | InterestingNumber(string, InterestingNumber.t)
  | Achievement(achievement);

type t = {
  date: Js.Date.t,
  source,
};

let timeUnit = (unit, adder, date, number) => {
  date: adder(number.InterestingNumber.value, date),
  source: InterestingNumber(unit, number),
};

let seconds = timeUnit("seconds", DateFns.addSeconds);

let minutes = timeUnit("minutes", DateFns.addMinutes);

let hours = timeUnit("hours", DateFns.addHours);

let days = timeUnit("days", DateFns.addDays);

let weeks = timeUnit("weeks", DateFns.addWeeks);

let months = timeUnit("months", DateFns.addMonths);

let years = timeUnit("years", DateFns.addYears);

let calculators = [seconds, minutes, hours, days, weeks, months, years];

let d = (year, month, day) =>
  Js.Date.makeWithYMD(
    float_of_int(year),
    float_of_int(month - 1),
    float_of_int(day),
    (),
  );

let achievements = [
  /* {name: "", achievement: "", birthday: d(), date: d()}, */
  {
    name: "Albert Einstein",
    achievement: "he published his famous E=mc^2 equation",
    birthday: d(1879, 3, 14),
    date: d(1905, 11, 21),
  },
  {
    name: "Mark Zuckerberg",
    achievement: "he launched Facebook from his dorm room",
    birthday: d(1984, 5, 14),
    date: d(2004, 2, 1),
  },
  {
    name: "Neil Armstrong",
    achievement: "he became the first human to set foot on the Moon",
    birthday: d(1930, 8, 5),
    date: d(1969, 7, 21),
  },
  {
    name: "Pablo Picasso",
    achievement: "he finished his masterpiece \"Guernica\"",
    birthday: d(1881, 10, 25),
    date: d(1937, 6, 4),
  },
];