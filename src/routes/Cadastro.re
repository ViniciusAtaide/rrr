open ReactNative;

[@react.component]
let make = (~navigation as _, ~route as _) => {
  let (name, setName) = React.useState(() => "");
  let (_password, _setPassword) = React.useState(() => "");

  <View>
    <Text> "Cadastro"->React.string </Text>
    <TextInput onChange={_ => setName(name => name)} />
    <Text> name->React.string </Text>
  </View>;
};