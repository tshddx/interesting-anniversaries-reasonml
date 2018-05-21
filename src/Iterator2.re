type iterator('a) = unit => iteration('a)
and iteration('a) =
  | Item('a, iterator('a))
  | StopIteration;

let rec count = start => {
  let i = ref(start);
  let rec loop = () => {
    let value = i^;
    i := value + 1;
    Item(value, loop);
  };
  loop;
};