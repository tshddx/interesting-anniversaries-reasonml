type item('output) =
  | Item('output)
  | StopIteration;

type iterator('state, 'output) = {
  mutable state: 'state,
  next: iterator('state, 'output) => item('output),
};

let rec each = (fn, iterator) =>
  switch (iterator.next(iterator)) {
  | Item(i) =>
    fn(i);
    each(fn, iterator);
  | StopIteration => ()
  };

let rec reduce = (accumulator, reducer, iterator) => {
  let item = iterator.next(iterator);
  switch (item) {
  | Item(i) =>
    let new_accumulator = reducer(accumulator, i);
    reduce(new_accumulator, reducer, iterator);
  | StopIteration => accumulator
  };
};

let rec take_while = (fn, iterator) => {
  state: (),
  next: _self => {
    let item = iterator.next(iterator);
    switch (item) {
    | Item(i) => fn(i) ? item : StopIteration
    | StopIteration => StopIteration
    };
  },
};

let rec map = (fn, iterator) => {
  ...iterator,
  next: _self => {
    let item = iterator.next(iterator);
    switch (item) {
    | Item(i) => Item(fn(i))
    | StopIteration => StopIteration
    };
  },
};

let rec filter = (fn, iterator) => {
  ...iterator,
  next: self => {
    let item = iterator.next(iterator);
    switch (item) {
    | Item(i) => fn(i) ? item : self.next(self)
    | StopIteration => StopIteration
    };
  },
};

let count = start => {
  state: start,
  next: self => {
    let i = self.state;
    self.state = i + 1;
    Item(i);
  },
};

let range = (first, last) => count(first) |> take_while(i => i <= last);

let times = n => range(0, n);
/* range(30, 80)
   |> filter(i => i mod 5 == 0)
   |> map(i => i * 10)
   |> each(Js.log); */