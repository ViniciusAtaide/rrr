module Query = [%relay.query
  {|
  query CredentialsQuery($cpfCnpj: String!) {
    userByCpfCnpj(cpfCnpj: $cpfCnpj) {
      _id
    }
  }
|}
];

let styles =
  ReactNative.Style.(
    ReactNative.StyleSheet.create({
      "bg": style(~backgroundColor="rgb(36, 37, 36)", ()),
      "container":
        style(
          ~alignItems=`flexStart,
          ~justifyContent=`center,
          ~height=100.->pct,
          ~padding=25.->dp,
          (),
        ),
      "txt":
        style(
          ~fontFamily="Montserrat-SemiBold",
          ~color="#fff",
          ~fontSize=24.,
          ~paddingTop=20.->dp,
          ~fontWeight=`_600,
          (),
        ),
      "txtBlk":
        style(
          ~fontFamily="Montserrat",
          ~color="black",
          ~fontSize=24.,
          ~lineHeight=48.,
          (),
        ),
      "txtLight":
        style(
          ~fontFamily="Montserrat-Light",
          ~color="black",
          ~fontSize=24.,
          ~lineHeight=48.,
          (),
        ),
      "orange":
        style(
          ~color="rgb(254,80,0)",
          ~fontFamily="Montserrat-Bold",
          ~fontSize=22.,
          (),
        ),
      "input":
        style(
          ~backgroundColor="#fff",
          ~marginTop=20.->dp,
          ~height=40.->dp,
          (),
        ),

      "wrapper": style(~flex=1., ~justifyContent=`flexEnd, ()),
      "buttonWrapper":
        style(~flex=1., ~width=100.->pct, ~justifyContent=`flexEnd, ()),
      "button":
        style(
          ~fontFamily="Montserrat-SemiBold",
          ~backgroundColor="#fff",
          ~fontSize=28.,
          ~width=100.->pct,
          ~alignItems=`center,
          (),
        ),
    })
  );

[@react.component]
let make = (~navigation, ~route as _) => {
  open Belt;

  let errorNoCpf = {j|CPF ou CNPJ obrigatórios|j};
  let environment = ReasonRelay.useEnvironmentFromContext();

  let (cpfcnpj, setCpfcnpj) = React.useState(_ => "");
  let (errors, setErrors) = React.useState(() => Set.String.empty);

  React.useEffect1(
    () => {
      switch (cpfcnpj) {
      | "" => setErrors(e => e->Set.String.add(errorNoCpf))
      | _ => setErrors(e => e->Set.String.remove(errorNoCpf))
      };
      None;
    },
    [|cpfcnpj|],
  );

  let submit = _ => {
    Js.Promise.(
      Query.fetch(~environment, ~variables={cpfCnpj: cpfcnpj})
      |> then_(user =>
           if (user) {
             navigation->RootNavigator.Navigation.navigate("Subscribe");
             resolve(true);
           } else {
             ReactNative.ToastAndroid.show(
               "CPF não encontrado, cadastre-se",
               ReactNative.ToastAndroid.long,
             );
             resolve(false);
           }
         )
    );
  };

  ReactNative.(
    <View style={styles##bg}>
      <KeyboardAvoidingView behavior=`height style={styles##container}>
        <SafeAreaView style={styles##wrapper}>
          <Text style={styles##orange}>
            {j|É sempre um prazer atender você!|j}->React.string
          </Text>
          <Text style={styles##txt}>
            "Para iniciarmos o atendimento, informe por gentileza o seu CPF ou CNPJ:"
            ->React.string
          </Text>
          <TextInput
            onChangeText={cnpj => setCpfcnpj(_ => cnpj)}
            returnKeyType=`go
            keyboardType=`numberPad
            style={styles##input}
          />
        </SafeAreaView>
        <View style={styles##buttonWrapper}>
          <View style={styles##button}>
            <TouchableNativeFeedback
              background={TouchableNativeFeedback.Background.ripple(
                "#000",
                false,
              )}
              onPress={_ =>
                errors->Set.String.isEmpty
                  ? submit() |> ignore
                  : ToastAndroid.(
                      showWithGravityAndOffset(
                        {j|CPF/CNPJ Obrigatórios|j},
                        long,
                        bottom,
                        ~xOffset=25.,
                        ~yOffset=50.,
                      )
                    )
              }>
              <Text
                style={Style.listOption([
                  errors->Set.String.isEmpty
                    ? Some(styles##txtBlk) : Some(styles##txtLight),
                ])}>
                "CONTINUAR"->React.string
              </Text>
            </TouchableNativeFeedback>
          </View>
        </View>
      </KeyboardAvoidingView>
    </View>
  );
};