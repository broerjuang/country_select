open Utils.Option;
open CoreUI;

module Trigger = {
  let component = ReasonReact.statelessComponent("Trigger");

  let make = (~isOpen, ~onKeyDown=?, ~selectedValue, ~onPress=?, _children) => {
    ...component,
    render: _self => {
      let customStyle =
        Css.(
          style([
            display(`flex),
            textAlign(`center),
            borderColor(`rgba((0, 0, 0, 0.2))),
            justifyContent(`spaceBetween),
            paddingRight(`px(5)),
            paddingLeft(`px(10)),
            alignItems(`center),
            maxWidth(`px(150)),
            borderRadius(`px(2)),
            borderWidth(`pxFloat(0.5)),
            backgroundColor(isOpen ? `hex("E0EBFD") : white),
          ])
        );
      let textStyle = Css.(style([color(black), textOverflow(`ellipsis)]));
      <button tabIndex=0 ?onKeyDown onClick=?onPress className=customStyle>
        <CoreUI.Text className=textStyle value=selectedValue />
        <Icon.ChevronDown />
      </button>;
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
      <View className=defaultStyle onPress=onClose />;
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
      <View className=defaultStyle> ...children </View>;
    },
  };
};

module Dropdown = {
  module Styles = {
    open ReactDOMRe.Style;
    let reactSelectStyle =
      ReactSelect.Select.styles(
        ~control=
          styles => {
            let overideStyle =
              make(
                ~display="flex",
                ~flexDirection="row-reverse",
                ~fontFamily="Arial",
                ~boxShadow="none",
                (),
              );
            combine(styles, overideStyle);
          },
        ~menu=
          styles => {
            let overideStyle =
              make(
                ~marginTop="0px",
                ~borderTopRightRadius="0px",
                ~borderTopLeftRadius="0px",
                (),
              );
            combine(styles, overideStyle);
          },
        (),
      );
  };
  let component = ReasonReact.statelessComponent("Dropdown");

  let make = (~onChange, _children) => {
    ...component,
    render: _self => {
      let renderOptions = props => {
        open ReactSelect.Select;
        let {label, value} = commonPropsFromJs(props);
        <ReactSelect.Components.Option props>
          <Row
            className=Css.(style([height(`px(30)), alignItems(`center)]))>
            <FlagIcon code={FlagIcon.codeFromJs(value)} />
            <CoreUI.Text
              className=Css.(style([marginLeft(`px(10))]))
              value=label
            />
          </Row>
        </ReactSelect.Components.Option>;
      };

      let renderSearchIcon = props => {
        <ReactSelect.Components.DropdownIndicator props>
          <Icon.Search />
        </ReactSelect.Components.DropdownIndicator>;
      };
      <Card>
        <ReactSelect.Select
          autoFocus=true
          onChange
          hideSelectedOptions=false
          menuIsOpen=true
          controlShouldRenderValue=false
          isClearable=false
          backspaceRemovesValue=false
          options=Mock.data
          placeholder="Search"
          styles=Styles.reactSelectStyle
          components={ReactSelect.Select.components(
            ~options=renderOptions,
            ~dropdownIndicator=renderSearchIcon,
            ~indicatorSeparator=_ => ReasonReact.null,
            (),
          )}
        />
      </Card>;
    },
  };
};

module ViewIf = {
  let component = ReasonReact.statelessComponent("ViewIf");

  let make = (~test, children) => {
    ...component,
    render: _self => {
      test ? <View> ...children </View> : ReasonReact.null;
    },
  };
};

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

  let make = _children => {
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
};