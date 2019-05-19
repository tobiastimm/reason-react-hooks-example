module Styles = {
  open Css;

  let card =
    style([
      display(`flex),
      overflow(`hidden),
      flexDirection(`column),
      justifyContent(`spaceBetween),
      height(rem(35.)),
      width(rem(35.)),
      backgroundColor(hex("fff")),
      `shadow(
        "0px 1px 3px 0px rgba(0,0,0,0.2),0px 1px 1px 0px rgba(0,0,0,0.14),0px 2px 1px -1px rgba(0,0,0,0.12)",
      ),
      borderRadius(px(4)),
      maxWidth(rem(35.)),
    ]);
  let cardImageWrapper =
    style([
      display(`flex),
      flexDirection(`column),
      position(`relative),
      height(px(280)),
    ]);
  let cardImage =
    style([
      display(`block),
      width(pct(100.)),
      height(pct(100.)),
      backgroundSize(`cover),
      backgroundRepeat(`noRepeat),
      unsafe("background-position", "center"),
    ]);
  let cardTitle =
    style([
      display(`inlineBlock),
      position(`absolute),
      right(px(-3)),
      bottom(px(-3)),
      fontSize(rem(3.)),
      transform(`rotate(deg(3))),
      fontWeight(`num(600)),
      padding(rem(0.75)),
      color(hex(Theme.colorBg)),
      backgroundColor(hex(Theme.colorPink)),
    ]);
  let cardContent =
    style([
      display(`flex),
      flexDirection(`column),
      height(rem(8.5)),
      padding(rem(1.6)),
    ]);
  let cardDescription =
    style([margin(`zero), fontSize(rem(1.4)), fontWeight(`num(400))]);
  let cardActions =
    style([display(`flex), justifyContent(`flexEnd), padding(rem(0.8))]);
  let cardAction =
    style([
      unsafe("flex", "0 0 auto"),
      color(hex(Theme.colorButton)),
      alignItems(`center),
      height(px(48)),
      justifyContent(`center),
      backgroundColor(`transparent),
      padding(rem(1.2)),
      fontSize(rem(2.4)),
      overflow(`visible),
      textAlign(`center),
      unsafe(
        "transition",
        "background-color 150ms cubic-bezier(0.4, 0, 0.2, 1) 0ms",
      ),
      unsafe("border", "none"),
      borderRadius(pct(50.)),
      margin(`zero),
      cursor(`pointer),
      hover([unsafe("background-color", "rgba(0, 0, 0, 0.08)")]),
    ]);
};

[@bs.deriving abstract]
type featherProps = {size: int};

[@react.component]
let make = (~recipe) =>
  <li className=Styles.card>
    <div className=Styles.cardImageWrapper>
      {switch (recipe##images) {
       | None => React.null
       | Some(images) =>
         let image = ArrayLabels.get(images, 0);
         let url = image##url;
         <div
           className=Styles.cardImage
           style={ReactDOMRe.Style.make(
             ~backgroundImage={j|url("$url")|j},
             (),
           )}
         />;
       }}
      <div className=Styles.cardTitle> {recipe##title |> React.string} </div>
    </div>
    <div className=Styles.cardContent>
      <p className=Styles.cardDescription>
        {recipe##description |> React.string}
      </p>
    </div>
    <div className=Styles.cardActions>
      <button className=Styles.cardAction>
        <FeaterIcons.Edit color={"#" ++ Theme.colorButton} />
      </button>
    </div>
  </li>;