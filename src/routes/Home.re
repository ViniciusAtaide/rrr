module Query = [%relay.query
  {|
  query HomeQuery {
    allUsers {
      edges {
        node {
          email
          name
        }
      }
    }
  }
|}
];

[@react.component]
let make = (~navigation, ~route as _) => {
  open ReactNative;

  let queryData = Query.use(~variables=(), ());

  let users = queryData.allUsers->Belt.Option.getWithDefault({edges: [||]});

  <SafeAreaView>
    <ScrollView contentInsetAdjustmentBehavior=`automatic>
      <View>
        <View>
          {users.edges
           ->Belt.Array.mapWithIndex((i, edge) =>
               switch (edge.node) {
               | Some(node) =>
                 <View key={string_of_int(i)}>
                   <Text>
                     {("Usuario: " ++ string_of_int(i + 1))->React.string}
                   </Text>
                   <Text> {("Nome: " ++ node.name)->React.string} </Text>
                   <Text> {("Email: " ++ node.email)->React.string} </Text>
                 </View>
               | None => "Nenhum Usuário"->React.string
               }
             )
           ->ReasonReact.array}
          <Button
            onPress={_ =>
              navigation->RootNavigator.Navigation.navigate("Cadastro")
            }
            title="Ir ao cadastro"
            color="#aaa"
          />
        </View>
      </View>
    </ScrollView>
  </SafeAreaView>;
};