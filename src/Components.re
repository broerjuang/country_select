open Utils.Option;

module Trigger = {
  let component = ReasonReact.statelessComponent("Trigger");

  let make = (~isOpen, ~onKeyDown=?, ~selectedValue, ~onPress=?, _children) => {
    ...component,
    render: _self => {
      let backgroundColor =
        Css.(
          isOpen ?
            style([backgroundColor(`hex("E0EBFD"))]) :
            style([backgroundColor(white)])
        );

      let customStyle =
        Css.(
          style([
            flexDirection(`row),
            borderColor(`rgba((0, 0, 0, 0.2))),
            justifyContent(`spaceBetween),
            paddingRight(`px(5)),
            paddingLeft(`px(10)),
            alignItems(`center),
            maxWidth(`px(150)),
            height(`px(30)),
            borderRadius(`px(2)),
            borderWidth(`pxFloat(0.5)),
          ])
        );
      let textStyle = Css.(style([color(black), textOverflow(`ellipsis)]));
      <CoreUI.TouchableOpacity
        tabIndex=0
        ?onKeyDown
        ?onPress
        className={Css.merge([backgroundColor, customStyle])}>
        <CoreUI.Text className=textStyle value=selectedValue />
        <Icon.ChevronDown />
      </CoreUI.TouchableOpacity>;
    },
  };
};

module Cover = {
  let defaultStyle =
    Css.(
      style([
        bottom(zero),
        left(zero),
        right(zero),
        top(zero),
        position(`fixed),
        zIndex(1),
      ])
    );
  let component = ReasonReact.statelessComponent("Cover");

  let make = (~onClose, _children) => {
    ...component,
    render: _self => {
      <CoreUI.View className=defaultStyle onPress=onClose />;
    },
  };
};

module Card = {
  let defaultStyle =
    Css.(
      style([
        position(`absolute),
        display(`block),
        zIndex(2),
        marginTop(`px(5)),
        minWidth(`px(250)),
        backgroundColor(white),
        border(`px(1), `solid, `rgba((0, 0, 0, 0.08))),
      ])
    );
  let component = ReasonReact.statelessComponent("Card");

  let make = children => {
    ...component,
    render: _self => {
      <CoreUI.View className=defaultStyle> ...children </CoreUI.View>;
    },
  };
};

module Dropdown = {};

module CountrySelect = {
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

  let make = _chilren => {
    ...component,
    initialState: () => {isOpen: false, selectedValue: None},
    reducer: (action, state) => {
      switch (action) {
      | ToggleDropdown =>
        ReasonReact.Update({...state, isOpen: !state.isOpen})
      | SelectValue(selectedValue) =>
        ReasonReact.Update({
          selectedValue: Some(selectedValue),
          isOpen: !state.isOpen,
        })
      };
    },
    render: ({state, send}) => {
      let renderOptions = props => {
        <ReactSelect.Components.Option props>
          <CoreUI.Row
            className=Css.(style([height(`px(30)), alignItems(`center)]))>
            <FlagIcon code={FlagIcon.codeFromJs(props##value)} />
            <CoreUI.Text
              className=Css.(style([marginLeft(`px(10))]))
              value=props##label
            />
          </CoreUI.Row>
        </ReactSelect.Components.Option>;
      };

      <CoreUI.View>
        <Trigger
          onPress={_ => send(ToggleDropdown)}
          isOpen={state.isOpen}
          selectedValue={
            state.selectedValue <$> (value => value##label) |? "Select Country"
          }
        />
        {state.isOpen ?
           <CoreUI.View>
             <Card>
               <ReactSelect.Select
                 autoFocus=true
                 onChange={value => send(SelectValue(value))}
                 hideSelectedOptions=false
                 menuIsOpen=true
                 controlShouldRenderValue=false
                 isClearable=false
                 backspaceRemovesValue=false
                 options=Mock.data
                 placeholder="Search"
                 styles={
                   "control": props =>
                     Js.Obj.assign(
                       props,
                       {
                         "display": "flex",
                         "flexDirection": "row-reverse",
                         "borderRadius": "0",
                         "fontFamily": "Arial",
                         "boxShadow": "none",
                       },
                     ),
                   "menu": props =>
                     Js.Obj.assign(
                       props,
                       {
                         "marginTop": "0",
                         "borderTopRightRadius": "0",
                         "borderTopLeftRadius": "0",
                       },
                     ),
                 }
                 components={
                   "Option": renderOptions,
                   "DropdownIndicator": props =>
                     <ReactSelect.Components.DropdownIndicator props>
                       <Icon.Search />
                     </ReactSelect.Components.DropdownIndicator>,
                   "IndicatorSeparator": Js.null,
                 }
               />
             </Card>
             <Cover onClose={_ => send(ToggleDropdown)} />
           </CoreUI.View> :
           ReasonReact.null}
      </CoreUI.View>;
    },
  };
};