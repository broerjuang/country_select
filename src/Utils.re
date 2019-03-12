module Option = {
  // I add the infix operator so it's easier to map optional value
  let (<$>) = Belt.Option.map;
  let (>>=) = Belt.Option.flatMap;
  let (|?) = (maybe, default) => {
    switch (maybe) {
    | Some(value) => value
    | None => default
    };
  };
};