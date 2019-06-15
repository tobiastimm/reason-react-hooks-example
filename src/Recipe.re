[@bs.val] external confirm: string => bool = "confirm";
exception GraphQLErrors(array(ReasonApolloTypes.graphqlError));
exception EmptyResponse;

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

module DeleteRecipeById = [%graphql
  {|
    mutation deleteRecipeById($id:ID!) {
      deleteRecipe(where: { id: $id}) {
        id
      }
    }
|}
];

module DeleteRecipeByIdMutation =
  ReasonApollo.CreateMutation(DeleteRecipeById);

[@bs.deriving abstract]
type featherProps = {size: int};

[@react.component]
let make = (~recipe) => {
  let handleEdit = id => ReasonReactRouter.push({j|recipe/$id/edit|j});

  <li className=Styles.card>
    <div className=Styles.cardImageWrapper>
      {switch (recipe##images) {
       | None => React.null
       | Some(images) =>
         let image =
           if (Array.length(images) > 0) {
             ArrayLabels.get(images, 0);
           } else {
             {"id": "", "url": ""};
           };
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
      <button
        className=Styles.cardAction onClick={_ => handleEdit(recipe##id)}>
        <FeatherIcons.Edit color={"#" ++ Theme.colorButton} />
      </button>
      <DeleteRecipeByIdMutation>
        ...{(mutation, _) => {
          let deleteRecipeByIdMutation =
            DeleteRecipeById.make(~id=recipe##id, ());
          <button
            onClick={_ => {
              let doDelete =
                confirm("Do you really want to delete this recipe?");
              if (doDelete == true) {
                mutation(
                  ~variables=deleteRecipeByIdMutation##variables,
                  ~refetchQueries=[|"getRecipes"|],
                  (),
                )
                |> Js.Promise.then_(res =>
                     switch (
                       (
                         res:
                           ReasonApolloTypes.executionResponse(
                             DeleteRecipeById.t,
                           )
                       )
                     ) {
                     | Data(_) => Js.Promise.resolve()
                     | Errors(error) =>
                       Js.log(error);
                       Js.Promise.reject(raise(GraphQLErrors(error)));
                     | EmptyResponse =>
                       Js.Promise.reject(raise(EmptyResponse))
                     }
                   )
                |> ignore;
              };
            }}
            className=Styles.cardAction>
            <FeatherIcons.Trash color={"#" ++ Theme.colorButton} />
          </button>;
        }}
      </DeleteRecipeByIdMutation>
    </div>
  </li>;
};