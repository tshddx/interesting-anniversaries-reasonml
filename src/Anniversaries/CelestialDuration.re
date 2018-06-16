type t = {
  name: string,
  number: int,
  date: Js.Date.t,
};

open Iterator;

let every = (multiple, ()) => count(1) |> filter(i => i mod multiple == 0);

let orbitalPeriods = [
  ("Mercury", 88.0, every(50)),
  ("Venus", 224.7, every(25)),
  ("Mars", 687.0, every(10)),
  ("Jupiter", 4331.0, every(1)),
  ("Saturn", 10747.0, every(1)),
  ("Uranus", 30589.0, every(1)),
  ("Neptune", 59800.0, every(1)),
  ("Pluto", 90560.0, every(1)),
];

let celestialDurations = (birthday, maxDate) =>
  orbitalPeriods
  |> List.map(((name, days, numberGenerator)) =>
       numberGenerator()
       |> map(number =>
            {
              name,
              number,
              date:
                birthday |> DateFns.addDays(days *. float_of_int(number)),
            }
          )
       |> takeWhile(({date}) => date |> DateFns.isBefore(maxDate))
       |> toList
     )
  |> List.concat;