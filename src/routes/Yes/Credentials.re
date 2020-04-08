module Query = [%relay.query
  {|
  query CredentialsQuery($cpfCnpj: String!) {
    userByCpfCnpj(cpfCnpj: $cpfCnpj) {
      _id
    }
  }
|}
];

module CredentialsForm = [%form
  {target: ReactNative};
  let regexCPFCNPJ = [%re
    "/(^\\d{3}\\.\\d{3}\\.\\d{3}\\-\\d{2}$)|(^\\d{2}\\.\\d{3}\\.\\d{3}\\/\\d{4}\\-\\d{2}$)/"
  ];
  module CpfCnpj = {
    type t = string;

    let validate = cpfcnpj => Js.String.match(regexCPFCNPJ, cpfcnpj);
  };
  type input = {cpfCnpj: CpfCnpj.t};
  let validators = {
    cpfCnpj: {
      strategy: OnFirstChange,
      validate: input =>
        switch (input.cpfCnpj) {
        | "" => Error({j|Campo obrigatório|j})
        | _ =>
          switch (input.cpfCnpj->CpfCnpj.validate) {
          | None => Error({j|Campo não formatado|j})
          | Some(_) => Ok(input.cpfCnpj)
          }
        },
    },
  }
];

let styles =
  ReactNative.Style.(
    ReactNative.StyleSheet.create({
      "bg": style(~backgroundColor="rgb(36, 37, 36)", ~height=100.->pct, ()),
      "container": style(~flex=1., ~padding=25.->dp, ()),
      "wrapper":
        style(~flex=1., ~justifyContent=`center, ~marginBottom=60.->dp, ()),
      "txt":
        style(
          ~fontFamily="Montserrat-SemiBold",
          ~color="#fff",
          ~fontSize=24.,
          ~paddingTop=20.->dp,
          ~fontWeight=`_600,
          (),
        ),
      "txtError": style(~color="red", ()),
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
      "errorMessageText":
        style(
          ~fontSize=16.,
          ~fontFamily="Montserrat-SemiBold",
          ~color="rgb(254,80,0)",
          (),
        ),
    })
  );

[@react.component]
let make = (~navigation, ~route as _) => {
  open ReactNative;

  let environment = ReasonRelay.useEnvironmentFromContext();

  let form =
    CredentialsForm.useForm(
      ~initialInput={cpfCnpj: ""}, ~onSubmit=(output, cb) => {
      Js.Promise.(
        Query.fetch(~environment, ~variables={cpfCnpj: output.cpfCnpj})
        |> then_((res: Query.Operation.response) => {
             switch (res.userByCpfCnpj) {
             | Some(_) =>
               navigation->Navigators.SubscribeNavigator.Navigation.navigateWithParams(
                 "Auth",
                 {cpfCnpj: output.cpfCnpj},
               );

               resolve(res);
             | None =>
               ReactNative.ToastAndroid.(
                 showWithGravityAndOffset(
                   {j|CPF não cadastrado no sistema|j},
                   long,
                   bottom,
                   ~xOffset=25.,
                   ~yOffset=50.,
                 )
               );

               cb.notifyOnFailure();
               reject(raise(Not_found));
             }
           })
      )
      |> ignore
    });

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
          onChangeText={cpfCnpj =>
            form.updateCpfCnpj(_ => {cpfCnpj: cpfCnpj})
          }
          returnKeyType=`go
          keyboardType=`numberPad
          style={styles##input}
        />
        {switch (form.cpfCnpjResult) {
         | Some(Error(message)) =>
           <View>
             <Text style={styles##errorMessageText}>
               message->React.string
             </Text>
           </View>
         | Some(Ok(_))
         | None => React.null
         }}
      </SafeAreaView>
      <SubmitButton valid={form.valid} submit={_ => form.submit()} />
    </KeyboardAvoidingView>
  </View>;
};