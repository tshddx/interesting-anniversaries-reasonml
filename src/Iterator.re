type iterator('a) = unit => iteration('a)
and iteration('a) =
  | Item('a, iterator('a))
  | StopIteration
and generator('a) = unit => iterator('a);

let create = (iterator: iterator('a)) => iterator;

let empty = () => StopIteration;

let just = item => create(() => Item(item, empty));

/* itertools that take and return generic iterators */
/* */
let rec chain = (first, secondGenerator) =>
  switch (first()) {
  | Item(item, next) =>
    create(() => Item(item, chain(next, secondGenerator)))
  | StopIteration => secondGenerator()
  };

let andThen = (secondGenerator, first) => chain(first, secondGenerator);

let rec mapRaw = (func, iterator) =>
  switch (iterator()) {
  | Item(item, next) => func(item, next)
  | StopIteration => empty
  };

/* Takes a `make_iterator` which takes an item and returns another iterator,
   then chains all the iterators together. */
let rec mapIter = (make_iterator, iterator) =>
  iterator
  |> mapRaw((item, next) =>
       make_iterator(item) |> andThen(() => next |> mapIter(make_iterator))
     );

let rec map = (func, iterator) =>
  iterator |> mapIter(item => just(func(item)));

let rec mapItem = (func, iterator) =>
  switch (iterator()) {
  | Item(item, next) => (() => func(item, next |> mapItem(func)))
  | StopIteration => empty
  };

let rec filter = (predicate, iterator) =>
  iterator |> mapIter(item => predicate(item) ? just(item) : empty);

let rec each = func =>
  map((item, _next) => {
    func(item);
    ();
  });

let rec cycle = iterator => iterator |> andThen(() => cycle(iterator));

let rec repeat = (item, ~count=?) =>
  switch (count) {
  | Some(c) => c <= 0 ? empty : repeat(item, ~count=c - 1)
  | None => cycle(just(item))
  };

let rec take = (count, iterator) =>
  if (count == 0) {
    empty;
  } else {
    switch (iterator()) {
    | Item(item, next) => just(item) |> andThen(() => take(count - 1, next))
    | StopIteration => empty
    };
  };

let rec takeWhile = (predicate, iterator) =>
  iterator
  |> mapItem((item, next) =>
       predicate(item) ? Item(item, next) : StopIteration
     );

/* Combinatorics */
/*  */
/* Takes item and iterator like [1, 2, 3, ...] and returns iterator like
   [(item, 1), (item, 2), (item, 3), ...] */
let withItem = (item, iterator) => iterator |> map(item' => (item, item'));

/* Takes two iterators and returns their cartesian product, i.e.
   product([a, b, c], [1, 2, 3]) is [(a, 1), (b, 2), (c, 3)] */
let product = (a, b) => a |> mapIter(a_item => b |> withItem(a_item));

let cons = size => ();

let slice = size => ();

let firstChunk = (isEqual, iterator) =>
  switch (iterator()) {
  | Item(item, next) =>
    let firstItem = item;
    just(firstItem)
    |> andThen(() => next |> takeWhile(item => isEqual(firstItem, item)));
  | StopIteration => empty
  };

let firstChunkAndRest = (isEqual, iterator) =>
  switch (iterator()) {
  | Item(firstItem, next) =>
    let firstChunk =
      just(firstItem)
      |> andThen(() => next |> takeWhile(item => isEqual(firstItem, item)));
    firstChunk;
  | StopIteration => empty
  };

let firstChunkBy = (makeKey, iterator) =>
  firstChunk((a, b) => makeKey(a) == makeKey(b));

let chunk = (isEqual, iterator) => {
  let rec helper = (currentChunk, previousItem, iterator) =>
    switch (iterator()) {
    | Item(item, next) =>
      isEqual(previousItem, item) ?
        helper(currentChunk |> andThen(() => just(item)), item, next) :
        currentChunk |> andThen(() => helper(empty, item, next))
    | StopIteration => currentChunk
    };
  switch (iterator()) {
  | Item(item, next) => helper(empty, item, next)
  | StopIteration => empty
  };
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

let range = (start, finish) => count(start) |> takeWhile(i => i <= finish);

let times = num => range(0, num - 1);

/* Converters to and from other data structures */
/*  */
let rec toList = iterator =>
  /* Note: it will get reversed */
  switch (iterator()) {
  | Item(item, next) => [item, ...toList(next)]
  | StopIteration => []
  };

let rec fromList = (items, ()) =>
  /* Note: it will get reversed */
  switch (items) {
  | [item, ...rest] => Item(item, fromList(rest))
  | [] => StopIteration
  };

let toArray = iterator => iterator |> toList |> Array.of_list;

let fromArray = array => array |> Array.to_list |> fromList;