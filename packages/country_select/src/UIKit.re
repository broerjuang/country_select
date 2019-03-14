open CoreUI;

module Trigger = {
  module Styles = {
    let customStyle = isOpen =>
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
  };
  let component = ReasonReact.statelessComponent("Trigger");

  let make = (~isOpen, ~onKeyDown=?, ~selectedValue, ~onPress=?, _children) => {
    ...component,
    render: _self => {
      <button
        tabIndex=0
        ?onKeyDown
        onClick=?onPress
        className={Styles.customStyle(isOpen)}>
        <CoreUI.Text className=Styles.textStyle value=selectedValue />
        <Icon.ChevronDown />
      </button>;
    },
  };
};

module Cover = {
  module Styles = {
    let default =
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
  };

  let component = ReasonReact.statelessComponent("Cover");

  let make = (~onClose, _children) => {
    ...component,
    render: _self => {
      <View className=Styles.default onPress=onClose />;
    },
  };
};

module Card = {
  module Styles = {
    let default =
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
  };

  let component = ReasonReact.statelessComponent("Card");

  let make = children => {
    ...component,
    render: _self => {
      <View className=Styles.default> ...children </View>;
    },
  };
};

module Menu = {
  let component = ReasonReact.statelessComponent("Menu");

  let make = (~props, _children) => {
    ...component,
    render: _self => {
      <ReactSelect.Components.MenuList props>
        <ReactWindow
          height=props##maxHeight
          itemCount={Array.length(props##children)}
          itemSize=35
          initialScrollOffset=(-35)>
          ...{values =>
            <div style=values##style> {props##children[values##index]} </div>
          }
        </ReactWindow>
      </ReactSelect.Components.MenuList>;
    },
  };
};

module Dropdown = {
  module Styles = {
    open ReactDOMRe.Style;
    let reactSelectStyle =
      ReactSelect.Shared.styles(
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

  let make =
      (
        ~className=?,
        ~selectedValue=?,
        ~withVirtualized=false,
        ~onChange,
        ~options,
        _children,
      ) => {
    ...component,
    render: _self => {
      let renderOptions = props => {
        <ReactSelect.Components.Option props>
          <Row
            className=Css.(style([height(`px(30)), alignItems(`center)]))>
            <FlagIcon code={FlagIcon.codeFromJs(props##value)} />
            <CoreUI.Text
              className=Css.(style([marginLeft(`px(10))]))
              value=props##label
            />
          </Row>
        </ReactSelect.Components.Option>;
      };

      let renderSearchIcon = props => {
        <ReactSelect.Components.DropdownIndicator props>
          <Icon.Search />
        </ReactSelect.Components.DropdownIndicator>;
      };

      let renderComponents =
        withVirtualized ?
          {
            ReactSelect.Shared.components(
              ~options=renderOptions,
              ~dropdownIndicator=renderSearchIcon,
              ~indicatorSeparator=_ => ReasonReact.null,
              ~menuList=props => <Menu props />,
              (),
            );
          } :
          {
            ReactSelect.Shared.components(
              ~options=renderOptions,
              ~dropdownIndicator=renderSearchIcon,
              ~indicatorSeparator=_ => ReasonReact.null,
              (),
            );
          };

      <Card>
        <ReactSelect.Select
          ?className
          value=selectedValue
          autoFocus=true
          onChange
          hideSelectedOptions=false
          menuIsOpen=true
          controlShouldRenderValue=false
          isClearable=false
          backspaceRemovesValue=false
          closeMenuOnSelect=true
          options
          placeholder="Search"
          styles=Styles.reactSelectStyle
          components=renderComponents
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