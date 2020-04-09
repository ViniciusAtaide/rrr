module SpeakForm = [%form
  {target: ReactNative};
  type input = {
    name: string,
    email: string,
  };
  let validators = {
    name: {
      strategy: OnFirstBlur,
      validate: input =>
        switch (input.name) {
        | "" => Error({j|Nome Obrigatório.|j})
        | _ => Ok(input.name)
        },
    },
    email: {
      strategy: OnFirstBlur,
      validate: input =>
        switch (input.email) {
        | "" => Error({j|Email Obrigatório|j})
        | _ =>
          switch (input.email->Utils.Email.validate) {
          | None => Error({j|Email não formatado|j})
          | Some(_) => Ok(input.email)
          }
        },
    },
  }
];

let styles =
  ReactNative.Style.(
    ReactNative.StyleSheet.create({
      "bg": style(~backgroundColor="rgb(36, 37, 36)", ~flex=1., ()),
      "container":
        style(~alignContent=`flexStart, ~padding=25.->dp, ~flex=1., ()),
      "wrapper": style(~flex=1., ~justifyContent=`center, ()),
      "txt":
        style(
          ~fontFamily="Montserrat-SemiBold",
          ~color="#fff",
          ~fontSize=22.,
          ~paddingTop=20.->dp,
          (),
        ),
      "txtBlk":
        style(
          ~fontFamily="Montserrat-Bold",
          ~color="black",
          ~fontSize=24.,
          ~lineHeight=48.,
          (),
        ),
      "txtGray":
        style(
          ~fontFamily="Montserrat-Light",
          ~color="gray",
          ~fontSize=24.,
          ~lineHeight=48.,
          (),
        ),
      "inputWrapper": style(~marginVertical=2.5->dp, ~width=100.->pct, ()),
      "input": style(~backgroundColor="#fff", ~height=40.->dp, ()),
      "orange":
        style(
          ~color="rgb(254,80,0)",
          ~fontFamily="Montserrat-Bold",
          ~fontSize=22.,
          (),
        ),

      "button":
        style(
          ~fontFamily="Montserrat-SemiBold",
          ~backgroundColor="#fff",
          ~fontSize=28.,
          ~width=100.->pct,
          ~alignItems=`center,
          (),
        ),
      "buttonWrapper": style(~flex=1., ~justifyContent=`flexEnd, ()),
      "errorMessage": style(~opacity=0., ()),
      "errorMessageText":
        style(
          ~fontSize=16.,
          ~fontFamily="Montserrat-SemiBold",
          ~color="rgb(254,80,0)",
          (),
        ),
      "errorMessageActive": style(~opacity=1., ()),
    })
  );

[@react.component]
let make = (~navigation as _, ~route as _) => {
  open React;
  open Belt;
  open ReactNative;

  let emailRef = useRef(Js.Nullable.null);

  let form =
    SpeakForm.useForm(
      ~initialInput={name: "", email: ""},
      ~onSubmit=(output, cb) => {
        let name = output.name;
        let email = output.email;

        let text = {j|Olá! Meu nome é $name e meu email é $email. Gostaria de falar com uma atendente.|j};
        let url = {j|whatsapp://send?text=$text&phone=5583999651707|j};

        Js.Promise.(
          Linking.openURL(url)
          |> then_(() => {
               cb.reset();
               resolve(true);
             })
          |> catch(_ => {
               cb.notifyOnFailure();
               resolve(false);
             })
        )
        |> ignore;
      },
    );

  <View style={styles##bg}>
    <KeyboardAvoidingView behavior=`height style={styles##container}>
      <SafeAreaView style={styles##wrapper}>
        <Text style={styles##orange}>
          {j|Vamos conversar?!|j}->React.string
        </Text>
        <View style={styles##inputWrapper}>
          <Text style={styles##txt}> "Qual seu nome?"->React.string </Text>
          <TextInput
            returnKeyType=`next
            blurOnSubmit=false
            style={styles##input}
            onChangeText={name => form.updateName(input => {...input, name})}
            onSubmitEditing={_ => {
              emailRef
              ->React.Ref.current
              ->Js.Nullable.toOption
              ->Option.map(email => email->TextInput.focus)
              ->ignore
            }}
          />
          {switch (form.nameResult) {
           | Some(Error(message)) =>
             <View>
               <Text style={styles##errorMessageText}>
                 message->React.string
               </Text>
             </View>
           | Some(Ok(_))
           | None => React.null
           }}
        </View>
        <View style={styles##inputWrapper}>
          <Text style={styles##txt}> "Informe seu E-Mail"->React.string </Text>
          <TextInput
            returnKeyType=`go
            style={styles##input}
            ref=emailRef
            onChangeText={email =>
              form.updateEmail(input => {...input, email})
            }
            onSubmitEditing={_ => form.submit()}
          />
          {switch (form.emailResult) {
           | Some(Error(message)) =>
             <View>
               <Text style={styles##errorMessageText}>
                 message->React.string
               </Text>
             </View>
           | Some(Ok(_))
           | None => React.null
           }}
        </View>
      </SafeAreaView>
      <SubmitButton
        valid={form.valid}
        loading={form.submitting}
        submit={form.submit}
      />
    </KeyboardAvoidingView>
  </View>;
};