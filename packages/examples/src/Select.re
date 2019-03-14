type state = option(string);
type action =
  | Select(string);

type render = {
  onSelect: string => unit,
  selectedValue: option(string),
};

let component = ReasonReact.reducerComponent("Select");

let make = children => {
  ...component,
  initialState: () => None,
  reducer: (action, _state) => {
    switch (action) {
    | Select(newState) => ReasonReact.Update(newState->Some)
    };
  },
  render: self =>
    children({
      onSelect: newState => self.send(Select(newState)),
      selectedValue: self.state,
    }),
};