/* https://github.com/bvaughn/react-virtualized/blob/master/source/WindowScroller/WindowScroller.example.js */
/* https://bvaughn.github.io/react-virtualized/#/components/WindowScroller */ 

type item = {
  a: string,
  b: int
};

let items = [|
             {a: "hi", b: 12345},
             {a: "bye", b: 88},
             {a: "good", b: 999},
             {a: "bad", b: 3333},
             {a: "hungry", b: 121},
             {a: "sad", b: 55},
             {a: "mad", b: 66},
             {a: "busy", b: 77},
             {a: "what", b: 883},
             {a: "python", b: -889},
             {a: "original", b: 848},
             {a: "john", b: -323},
             {a: "left", b: 1},
             {a: "right", b: 2},
             {a: "quiet", b: 92},
             {a: "scream", b: 8},
             {a: "abc", b: 7},
             {a: "123", b: 4},
             {a: "thing", b: 3},
             {a: "not", b: 38},
             {a: "matter", b: 100000000},
             {a: "person", b: 45},
             {a: "boy", b: 23},
             {a: "cry", b: 12},
             {a: "girl", b: 80},
             {a: "dinner", b: 993},
             {a: "lunch", b: 91},
             {a: "breakfast", b: 88},
             {a: "morning", b: 281},
             {a: "night", b: 323},
             {a: "noon", b: 2},
             {a: "rest", b: 99},
             {a: "nap", b: 885},
             {a: "power", b: 77},
             {a: "computer", b: 12},
             {a: "on", b: 32},
             {a: "off", b: 894839743973},
             {a: "context", b: 8},
             {a: "page", b: 83},
             
|];

type state = {
  scrollToIndex: int
};

type action =
  | UpdateScrollToIndex(int);

let reducer = (action, _state) =>
  switch (action) {
  | UpdateScrollToIndex(value) => ReasonReact.Update({scrollToIndex: value})
  };

let component = ReasonReact.reducerComponent("Example");

let noRowsRenderer = <div>(ReasonReact.string("No rows"))</div>;

/* .rowScrolling::after { */
/*   content: ': scrolling'; */
/*   font-size: 0.65rem; */
/*   color: #aaa; */
/* } */

let setListEl: (Js.nullable(ReasonReact.reactRef)) => unit = [%raw (a) => "{window.listEl = a}"];

let make = _children => {
  ...component,
  initialState: () => {
    scrollToIndex: -1
  },
  reducer,
  render: self => {
    let list = [|"George", "Lisa", "Ahmed", "Rhys", "Rachel", "Fatima", "Alberto", "Sarah", "Seamus", "George", "Lisa", "Ahmed", "Rhys", "Rachel", "Fatima", "Alberto", "Sarah", "Seamus", "George", "Lisa", "Ahmed", "Rhys", "Rachel", "Fatima", "Alberto", "Sarah", "Seamus", "George", "Lisa", "Ahmed", "Rhys", "Rachel", "Fatima", "Alberto", "Sarah", "Seamus", "George", "Lisa", "Ahmed", "Rhys", "Rachel", "Fatima", "Alberto", "Sarah", "Seamus", "George", "Lisa", "Ahmed", "Rhys", "Rachel", "Fatima", "Alberto", "Sarah", "Seamus" ,"George", "Lisa", "Ahmed", "Rhys", "Rachel", "Fatima", "Alberto", "Sarah", "Seamus" , "George", "Lisa", "Ahmed", "Rhys", "Rachel", "Fatima", "Alberto", "Sarah", "Seamus", "George", "Lisa", "Ahmed", "Rhys", "Rachel", "Fatima", "Alberto", "Sarah", "Seamus", "George", "Lisa", "Ahmed", "Rhys", "Rachel", "Fatima", "Alberto", "Sarah", "Seamus", "George", "Lisa", "Ahmed", "Rhys", "Rachel", "Fatima", "Alberto", "Sarah", "Seamus", "George", "Lisa", "Ahmed", "Rhys", "Rachel", "Fatima", "Alberto", "Sarah", "Seamus", "George", "Lisa", "Ahmed", "Rhys", "Rachel", "Fatima", "Alberto", "Sarah", "Seamus" ,"George", "Lisa", "Ahmed", "Rhys", "Rachel", "Fatima", "Alberto", "Sarah", "Seamus", "George", "Lisa", "Ahmed", "Rhys", "Rachel", "Fatima", "Alberto", "Sarah", "Seamus", "George", "Lisa", "Ahmed", "Rhys", "Rachel", "Fatima", "Alberto", "Sarah", "Seamus", "George", "Lisa", "Ahmed", "Rhys", "Rachel", "Fatima", "Alberto", "Sarah", "Seamus" ,"George", "Lisa", "Ahmed", "Rhys", "Rachel", "Fatima", "Alberto", "Sarah", "Seamus", "George", "Lisa", "Ahmed", "Rhys", "Rachel", "Fatima", "Alberto", "Sarah", "Seamus", "George", "Lisa", "Ahmed", "Rhys", "Rachel", "Fatima", "Alberto", "Sarah", "Seamus", "George", "Lisa", "Ahmed", "Rhys", "Rachel", "Fatima", "Alberto", "Sarah", "Seamus", "George", "Lisa", "Ahmed", "Rhys", "Rachel", "Fatima", "Alberto", "Sarah", "Seamus"|];
    
    let rowRenderer = (rowRenderParams: List.rowRenderParams) => {
      /* Js.log(rowRenderParams); */
      let row = list[rowRenderParams |. List.index];  
      /* const className = cn(styles.row, { */
      /*   [styles.rowScrolling]: isScrolling, */
      /*   isVisible: isVisible, */
      /* }); */
      let className = if (rowRenderParams |. List.isVisible) {
        "isVisible"
      } else {
        ""
      };

      let className' = className ++ if (rowRenderParams |. List.isScrolling) {
        " rowScrolling"
      } else {
        ""
      };

      <div key=(rowRenderParams |. List.key) className=className'>
        (ReasonReact.string(row))
      </div>
    };
    
    <div>
      <WindowScroller>
        ((wp: WindowScroller.params) => {
          Js.log("wp");
          Js.log(wp);  
          <AutoSizer>
            ((ap: AutoSizer.params) => {
              Js.log("ap");
              Js.log(ap);
              <div ref=(wp |. WindowScroller.registerChild)>
              <List
                ref=((el) => {(setListEl(el))})    
                autoHeight=(true)
                height=(wp |. WindowScroller.height)
                isScrolling=(wp |. WindowScroller.isScrolling)
                onScroll=(wp |. WindowScroller.onChildScroll)
                overscanRowCount=(2)
                rowCount=(Array.length(list))
                rowHeight=(30)
                rowRenderer=(rowRenderer)
                scrollToIndex=(self.state.scrollToIndex)
                scrollTop=(wp |. WindowScroller.scrollTop)
                width=(ap |. AutoSizer.width)
              />
              </div>
            })
          </AutoSizer>
        })
      </WindowScroller>
      /* <WindowScroller> */
      /*   ((wp: WindowScroller.params) => { */
      /*     /\* <AutoSizer> *\/ */
      /*      /\*   ((asize: AutoSizer.params) => { *\/ */
      /*     Js.log("autoSizer"); */
      /*     let rows = Array.mapi((idx, item: item) => { */
      /*         [| (<div style=(ReactDOMRe.Style.make(~width="80px", ()))> */
      /*               (ReasonReact.string(item.a)) */
      /*             </div>) */
      /*          ,  (<div style=(ReactDOMRe.Style.make(~width="80px", ()))> */
      /*               (ReasonReact.string(string_of_int(item.b))) */
      /*             </div>) */
      /*           |] |> ReasonReact.array */
      /*        }, items); */

      /*     let columns = [| */
      /*       <Table.Column label="Column A" dataKey="a" flexGrow=1 />, */
      /*       <Table.Column label="Column B" dataKey="b" flexGrow=1 />, */
      /*     |]; */

      /*     let rowRenderer = (rowRenderParams: Table.rowRenderParams) => { */
      /*       <div key=(rowRenderParams |. Table.key) style=(ReactDOMRe.Style.make(~display="flex", ~flexDirection="row", ()))> */
      /*         (rows[rowRenderParams |. Table.index]) */
      /*       </div> */
      /*     }; */
      
      /*     <Table */
      /*     /\* height=(wp |. WindowScroller.height) *\/ */
      /*       height=(600) */
      /*       isScrolling=(wp |. WindowScroller.isScrolling) */
      /*       rowHeight=(150) */
      /*       scrollToIndex=(0) */
      /*       scrollTop=(0) */
      /*       width=(1000) */
      /*       rowRenderer=rowRenderer */
      /*       rows=rows */
      /*       columns=columns */
      /*       columnWidth=(123) */
      /*     /> */
      /*   }) */
      /* </WindowScroller> */
    </div>
  }
};
