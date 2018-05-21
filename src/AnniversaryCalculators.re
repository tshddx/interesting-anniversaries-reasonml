type anniversary = {
  date: Js.Date.t,
  units: string,
  number: NumberGenerators.number,
};

type calculator = (Js.Date.t, NumberGenerators.number) => anniversary;

let seconds: calculator =
  (date, number) => {
    date: DateFns.addSeconds(number.value |> Utils.intToFloat, date),
    units: "seconds",
    number,
  };