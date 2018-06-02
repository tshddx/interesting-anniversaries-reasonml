open Iterator;

let generate = birthday => {
  let maxDate = DateFns.addYears(150.0, birthday);
  let generators = InterestingNumber.generators |> from_list;
  let calculators = Anniversary.calculators |> from_list;
  let pairs = product(generators, calculators);
  let iterator =
    pairs
    |> map(((generator, calculator)) => {
         let anns =
           generator() |> map(number => calculator(birthday, number));
         let anns =
           anns
           |> take_while((ann: Anniversary.t) =>
                ann.date |> DateFns.isBefore(maxDate)
              );
         anns |> to_list;
       });
  let lists = iterator |> to_list;
  let anniversaries = List.concat(lists);
  let achievements =
    Anniversary.achievements
    |> List.map((achievement: Anniversary.achievement) => {
         let difference =
           DateFns.differenceInCalendarDays(
             achievement.date,
             achievement.birthday,
           );
         let date = DateFns.addDays(difference, birthday);
         Anniversary.{date, source: Achievement(achievement)};
       });
  List.append(anniversaries, achievements)
  |> List.sort((a: Anniversary.t, b: Anniversary.t) =>
       compare(DateFns.getTime(a.date), DateFns.getTime(b.date))
     );
};

type anniversaryList = {
  past: array(Anniversary.t),
  shownPast: array(Anniversary.t),
  future: array(Anniversary.t),
};

let get = (birthday, now, beforeNow) => {
  let anniversaries = generate(birthday);
  let isPast = (ann: Anniversary.t) => ann.date |> DateFns.isBefore(now);
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