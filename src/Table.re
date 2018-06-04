[%bs.raw {|require('react-virtualized/styles.css')|}];

[@bs.module "react-virtualized"]
external column : ReasonReact.reactClass = "Column";

[@bs.module "react-virtualized"]
external table : ReasonReact.reactClass = "Table";

[@bs.deriving abstract]
type rowRenderParams = {
  index: int,
  key: string
};

type rowRenderer = rowRenderParams => ReasonReact.reactElement;

module Column = {
  let component = ReasonReact.statelessComponent("Column");
  let make = (~label: string, ~dataKey: string, ~flexGrow=0, ~width=80, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=column,
      ~props={
        "label": label,
        "dataKey": dataKey,
        "flexGrow": flexGrow,
        "width": width
      },
      children
    );
};

let make = (~height: int,
            ~isScrolling: bool,
            ~rowHeight: int,
            ~scrollToIndex: int,
            ~scrollTop: int,
            ~width: int,
            ~rowRenderer: rowRenderer,
            ~rows: array(ReasonReact.reactElement),
            ~columns: array(ReasonReact.reactElement),
            ~columnWidth: int,
            children) => {
  ReasonReact.wrapJsForReason(
    ~reactClass=table,
    ~props={
      "columnCount": Array.length(columns),
      "columnWidth": columnWidth,
      "height": height,
      "isScrolling": isScrolling,
      "overscanRowCount": 2,
      "rowCount": Array.length(rows),
      "rowGetter": ((a) => rows[a##index]),
      "rowHeight": rowHeight,
      "rowRenderer": rowRenderer,
      "scrollToIndex": scrollToIndex,
      "scrollTop": scrollTop,
      "width": width
    },
    Array.append(children, columns)
  );
};
