module Styles = {
  open Css;

  let recipeList =
    style([
      listStyleType(`none),
      display(`grid),
      gridTemplateColumns([
        `repeat((`autoFill, `minmax((rem(35.), fr(1.))))),
      ]),
      gridGap(rem(2.5)),
      gridAutoRows(rem(35.)),
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
        id
        url
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
          let recipes =
            Belt.Array.keepMap(response##recipes, recipe => recipe);
          recipes
          |> Array.map(recipe => <Recipe key=recipe##id recipe />)
          |> React.array;
        }
      }
    </GetRecipesQuery>
  </ul>;
};