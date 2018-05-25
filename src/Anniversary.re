type t = {
  date: Js.Date.t,
  units: string,
  number: InterestingNumber.t,
};

/* type calculator = (Js.Date.t, InterestingNumber.t) => t; */
let seconds = (date, number) => {
  date: DateFns.addSeconds(number.InterestingNumber.value, date),
  units: "seconds",
  number,
};

let minutes = (date, number) => {
  date: DateFns.addMinutes(number.InterestingNumber.value, date),
  units: "minutes",
  number,
};

let hours = (date, number) => {
  date: DateFns.addHours(number.InterestingNumber.value, date),
  units: "hours",
  number,
};

let days = (date, number) => {
  date: DateFns.addDays(number.InterestingNumber.value, date),
  units: "days",
  number,
};

let weeks = (date, number) => {
  date: DateFns.addWeeks(number.InterestingNumber.value, date),
  units: "weeks",
  number,
};

let months = (date, number) => {
  date: DateFns.addMonths(number.InterestingNumber.value, date),
  units: "months",
  number,
};

let years = (date, number) => {
  date: DateFns.addYears(number.InterestingNumber.value, date),
  units: "years",
  number,
};

let calculators = [seconds, minutes, hours, days, weeks, months, years];