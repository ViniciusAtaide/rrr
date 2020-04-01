module Query = [%relay.query
  {|
  query HomeQuery {
    allUsers(first: 2147483647) @connection(key: "HomeQuery_allUsers") {
      edges {
        node {
          _id
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
           ->Belt.Array.map(edge =>
               switch (edge.node) {
               | Some(node) =>
                 <View key={string_of_int(node._id)}>
                   <Text>
                     {("Usuario: " ++ string_of_int(node._id))->React.string}
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