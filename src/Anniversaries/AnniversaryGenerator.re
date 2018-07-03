open Iterator;

let generate = birthday => {
  let maxDate = DateFns.addYears(150.0, birthday);
  let interestingNumbers =
    Anniversary.interestingNumbers(birthday, maxDate) |> List.concat;
  let achievements = Anniversary.achievements(birthday, maxDate);
  let celestialDurations = Anniversary.celestialDurations(birthday, maxDate);
  let all = ref([]);
  /* Todo: make the types of anniversaries shows customizable. */
  if (true) {
    all := List.append(all^, interestingNumbers);
  };
  if (true) {
    all := List.append(all^, achievements);
  };
  if (true) {
    all := List.append(all^, celestialDurations);
  };
  let anniversaries =
    all^
    |> List.sort((a: Anniversary.t, b: Anniversary.t) =>
         compare(DateFns.getTime(a.date), DateFns.getTime(b.date))
       );
  anniversaries;
};

type anniversaryList = {
  past: array(Anniversary.t),
  shownPast: array(Anniversary.t),
  future: array(Anniversary.t),
};

let get = (birthday, now, beforeNow) => {
  let anniversaries = generate(birthday);
  let isPast = (ann: Anniversary.t) =>
    ann.date |> DateFns.isBefore(now |> DateFns.startOfDay);
  let (past, future) = anniversaries |> List.partition(isPast);
  let past = past |> Array.of_list;
  let future = future |> Array.of_list;
  let length = Array.length(past);
  let beforeNow = min(beforeNow, length);
  let countShown = beforeNow;
  let countHidden = length - countShown;
  let hiddenPast = Array.sub(past, 0, countHidden);
  let shownPast =
    countShown == 0 ? [||] : Array.sub(past, length - countShown, countShown);
  {past: hiddenPast, shownPast, future};
};