type iterator('a) = unit => iteration('a)
and iteration('a) =
  | Item('a, iterator('a))
  | StopIteration
and generator('a) = unit => iterator('a);

let from = iteration : iterator('a) => () => iteration;

let stop = from(StopIteration);

let just = item => from(Item(item, stop));

/* itertools that take and return generic iterators */
/* */
let rec chain = (first, second_generator) =>
  switch (first()) {
  | Item(item, next) => (() => Item(item, chain(next, second_generator)))
  | StopIteration => second_generator()
  };

let and_then = (second_generator, first) => chain(first, second_generator);

let rec map_raw = (itemFunc, stopFunc, iterator: iterator('a)) =>
  switch (iterator()) {
  | Item(item, next) => itemFunc(item, map_raw(itemFunc, stopFunc, next))
  | StopIteration => stopFunc()
  };

let rec map = (func, iterator) =>
  switch (iterator()) {
  | Item(item, next) => (() => Item(func(item), map(func, next)))
  | StopIteration => stop
  };

/* Takes a `make_iterator` which takes an item and returns another iterator,
   then chains all the iterators together. */
let rec map_iter = (make_iterator, iterator) =>
  switch (iterator()) {
  | Item(item, next) =>
    make_iterator(item) |> and_then(() => next |> map_iter(make_iterator))
  | StopIteration => stop
  };

let rec map_item = (func, iterator) =>
  switch (iterator()) {
  | Item(item, next) => (() => func(item, next |> map_item(func)))
  | StopIteration => stop
  };

/* let rec map_iter = (make_iterator, iterator) =>
   switch (iterator()) {
   | Item(item, next) =>
     let iter = make_iterator(item);
     ();
   | StopIteration => stop
   }; */
let rec each = (func, iterator) => {
  switch (iterator()) {
  | Item(item, next) =>
    func(item);
    each(func, next);
  | StopIteration => ()
  };
  ();
};

let rec cycle = iterator => iterator |> and_then(() => cycle(iterator));

let rec repeat = (item, ~count=?) =>
  switch (count) {
  | Some(c) => c <= 0 ? stop : repeat(item, ~count=c - 1)
  | None => cycle(just(item))
  };

let rec take = (count, iterator) =>
  if (count == 0) {
    stop;
  } else {
    switch (iterator()) {
    | Item(item, next) =>
      just(item) |> and_then(() => take(count - 1, next))
    | StopIteration => stop
    };
  };

let rec take_while = (predicate, iterator) =>
  iterator
  |> map_item((item, next) =>
       predicate(item) ? Item(item, next) : StopIteration
     );

/* Combinatorics */
/*  */
/* Takes item and iterator like [1, 2, 3, ...] and returns iterator like
   [(item, 1), (item, 2), (item, 3), ...] */
let with_item = (item, iterator) => iterator |> map(item' => (item, item'));

/* Takes two iterators and returns their cartesian product, i.e.
   product([a, b, c], [1, 2, 3]) is [(a, 1), (b, 2), (c, 3)] */
let product = (a, b) => a |> map_iter(a_item => b |> with_item(a_item));

let cons = size => ();

let slice = (size, iterator) => {
  /* let current = ref([]);
     let rec helper = size => {
       iterator |> map_item((item, next) => {
         if (i == 1) {
           Item(current^, next);
         } else {
           curent := [item, ..helper(size - 1, iterator)];
         };
       });
     };
        helper(size); */
};

/* itertools that take and return iterators of specific types */
/* */
let count = start => {
  let i = ref(start);
  let rec loop = () => {
    let value = i^;
    i := value + 1;
    Item(value, loop);
  };
  loop;
};

let range = (start, finish) => count(start) |> take_while(i => i <= finish);

let times = num => range(0, num - 1);

/* Converters to and from other data structures */
/*  */
let rec to_list = iterator =>
  /* Note: it will get reversed */
  switch (iterator()) {
  | Item(item, next) => [item, ...to_list(next)]
  | StopIteration => []
  /* let items = ref([]);
     iterator |> each(item => items := [item, ...items^]);
     items^; */
  };

let rec from_list = (items, ()) =>
  /* Note: it will get reversed */
  switch (items) {
  | [item, ...rest] => Item(item, from_list(rest))
  | [] => StopIteration
  };

let to_array = iterator => iterator |> to_list |> Array.of_list;

let from_array = array => array |> Array.to_list |> from_list;