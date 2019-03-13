/*
 import { FixedSizeList as List } from "react-window";
  class MenuList extends Component {
    render() {
      const { options, children, maxHeight, getValue } = this.props;
      const [value] = getValue();
      const initialOffset = options.indexOf(value) * height;

      return (
        <List
          height={maxHeight}
          itemCount={children.length}
          itemSize={height}
          initialScrollOffset={initialOffset}
        >
          {({ index, style }) => <div style={style}>{children[index]}</div>}
        </List>
      );
    }
  }

  */

module ReactWindow = {
  [@bs.module "react-window"]
  external reactClass: ReasonReact.reactClass = "FixedSizeList";

  [@bs.obj]
  external makeProps:
    (
      ~height: int,
      ~itemCount: int,
      ~itemSize: int,
      ~initialScrollOffset: int,
      unit
    ) =>
    _ =
    "";

  let make = (~height, ~itemCount, ~itemSize, ~initialScrollOffset, children) => {
    ReasonReact.wrapJsForReason(
      ~reactClass,
      ~props={
        "height": height,
        "itemCounte": itemCount,
        "itemSize": itemSize,
        "initialScrollOffset": initialScrollOffset,
        "width": 200,
      },
      children,
    );
  };
};

module Menu = {
  let component = ReasonReact.statelessComponent("Menu");

  let make = (~props, children) => {
    ...component,
    render: _self => {
      <ReactWindow
        height=props##maxHeight
        itemCount={Array.length(children)}
        itemSize=12
        initialScrollOffset=(-35)>
        ...{values => values}
      </ReactWindow>;
    },
  };
};