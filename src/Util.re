let rec replaceAll = (~value: 'a, ~with_: 'a, l: list('a)) => {
  let replaceOne = x =>
    if (x == value) {
      with_;
    } else {
      x;
    };
  switch (l) {
  | [] => []
  | [head, ...tail] => [
      replaceOne(head),
      ...replaceAll(~value, ~with_, tail),
    ]
  };
};

let rec replaceKey = (~key: 'a, ~with_: ('a, 'b), l: list(('a, 'b))) => {
  let replaceOne = ((elementKey, _) as x) =>
    if (elementKey == key) {
      with_;
    } else {
      x;
    };
  switch (l) {
  | [] => []
  | [head, ...tail] => [
      replaceOne(head),
      ...replaceKey(~key, ~with_, tail),
    ]
  };
};

let contains = (~value: 'a, theList: list('a)) => {
  let f = (found, elem) => found || elem == value;
  ListLabels.fold_left(~f, ~init=false, theList);
};

let containsKey = (~value: 'a, theList: list(('a, 'b))) => {
  let f = (found, eleme) =>
    found
    || {
      let (key, _) = eleme;
      key == value;
    };
  ListLabels.fold_left(~f, ~init=false, theList);
};