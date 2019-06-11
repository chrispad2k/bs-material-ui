module Classes = {
  type classesType =
    | Root(string)
    | Focused(string)
    | Disabled(string)
    | Error(string)
    | Filled(string)
    | Required(string)
    | Asterisk(string);
  type t = list(classesType);
  let to_string =
    fun
    | Root(_) => "root"
    | Focused(_) => "focused"
    | Disabled(_) => "disabled"
    | Error(_) => "error"
    | Filled(_) => "filled"
    | Required(_) => "required"
    | Asterisk(_) => "asterisk";
  let to_obj = listOfClasses =>
    listOfClasses->(
                     Belt.List.reduce(
                       Js.Dict.empty(),
                       (obj, classType) => {
                         switch (classType) {
                         | Root(className)
                         | Focused(className)
                         | Disabled(className)
                         | Error(className)
                         | Filled(className)
                         | Required(className)
                         | Asterisk(className) =>
                           Js.Dict.set(obj, to_string(classType), className)
                         };
                         obj;
                       },
                     )
                   );
};

[@bs.obj]
external makePropsMui:
  (
    ~children: 'children=?,
    ~className: string=?,
    ~disabled: bool=?,
    ~error: bool=?,
    ~filled: bool=?,
    ~focused: bool=?,
    ~muiFormControl: Js.t({..})=?,
    ~required: bool=?,
    ~classes: Js.Dict.t(string)=?,
    ~style: ReactDOMRe.Style.t=?,
    unit
  ) =>
  _ =
  "";

[@bs.module "@material-ui/core"]
external reactComponent: React.component('a) = "FormLabel";

[@react.component]
let make =
    (
      ~children: option('children)=?,
      ~className: option(string)=?,
      ~disabled: option(bool)=?,
      ~error: option(bool)=?,
      ~filled: option(bool)=?,
      ~focused: option(bool)=?,
      ~muiFormControl: option(Js.t({..}))=?,
      ~required: option(bool)=?,
      ~classes: option(Classes.t)=?,
      ~style: option(ReactDOMRe.Style.t)=?,
    ) =>
  React.createElement(
    reactComponent,
    makePropsMui(
      ~children?,
      ~className?,
      ~disabled?,
      ~error?,
      ~filled?,
      ~focused?,
      ~muiFormControl?,
      ~required?,
      ~classes=?Belt.Option.map(classes, v => Classes.to_obj(v)),
      ~style?,
      (),
    ),
  );
