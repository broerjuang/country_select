open Utils.Option;
open CoreUI;
open UIKit;

type value = {
  .
  "label": string,
  "value": string,
};

type state = {
  isOpen: bool,
  selectedValue: option(value),
};

type action =
  | ToggleDropdown
  | SelectValue(value);

let component = ReasonReact.reducerComponent("State");

let make = _children => {
  ...component,
  initialState: () => {isOpen: false, selectedValue: None},
  reducer: (action, state) => {
    switch (action) {
    | ToggleDropdown => ReasonReact.Update({...state, isOpen: !state.isOpen})
    | SelectValue(selectedValue) =>
      ReasonReact.Update({
        selectedValue: Some(selectedValue),
        isOpen: !state.isOpen,
      })
    };
  },
  render: ({state, send}) => {
    <View>
      <Trigger
        onPress={_ => send(ToggleDropdown)}
        isOpen={state.isOpen}
        selectedValue={
          state.selectedValue <$> (value => value##label) |? "Select Country"
        }
      />
      <ViewIf test={state.isOpen}>
        <Dropdown onChange={value => send(SelectValue(value))} />
        <Cover onClose={_ => send(ToggleDropdown)} />
      </ViewIf>
    </View>;
  },
};