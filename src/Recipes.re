module Styles = {
  open Css;

  let recipeList =
    style([
      listStyleType(`none),
      display(`grid),
      gridTemplateColumns([
        `repeat((`autoFill, `minmax((rem(30.), fr(1.))))),
      ]),
      gridGap(rem(2.5)),
      gridAutoRows(rem(30.)),
    ]);
};

module GetRecipes = [%graphql
  {|
  query getRecipes {
    recipes {
      id
      title
      description
      updatedAt
      createdAt
      images {
        status
        updatedAt
        createdAt
        id
        handle
        fileName
        height
        width
        size
        mimeType
      }
    }
  }
  |}
];

module GetRecipesQuery = ReasonApollo.CreateQuery(GetRecipes);

[@react.component]
let make = () => {
  let recipesQuery = GetRecipes.make();
  <ul className=Styles.recipeList>
    <GetRecipesQuery variables=recipesQuery##variables>
      ...{({result}) =>
        switch (result) {
        | Loading => <div> {React.string("Loading")} </div>
        | Error(error) => <div> {React.string(error##message)} </div>
        | Data(response) =>
          response##recipes
          |> Js.Array.map(recipe => <Recipe key={recipe##id} recipe />)
          |> React.array
        }
      }
    </GetRecipesQuery>
  </ul>;
};