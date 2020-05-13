module Query = [%relay.query
  {|
  query OptionsQuery($cpfCnpj: String!) {
    userByCpfCnpj(cpfCnpj: $cpfCnpj) {
      name
      cpfCnpj
    }
  }
|}
];

let styles =
  ReactNative.Style.(
    ReactNative.StyleSheet.create({
      "bg": style(~backgroundColor="rgb(36, 37, 36)", ()),
      "top": style(~paddingHorizontal=12.5->dp, ()),
      "container":
        style(
          ~justifyContent=`center,
          ~height=100.->pct,
          ~paddingTop=10.->dp,
          ~paddingHorizontal=12.5->dp,
          (),
        ),
      "txt":
        style(
          ~fontFamily="Montserrat-SemiBold",
          ~color="#000",
          ~fontSize=16.,
          ~textAlign=`center,
          (),
        ),
      "orange":
        style(
          ~color="rgb(254,80,0)",
          ~fontFamily="Montserrat-SemiBold",
          ~fontSize=26.,
          ~width=200.->dp,
          ~marginBottom=40.->dp,
          (),
        ),
      "horizontal":
        style(
          ~flexWrap=`wrap,
          ~flexDirection=`row,
          ~justifyContent=`spaceBetween,
          (),
        ),
      "button":
        style(
          ~backgroundColor="rgb(144,144,144)",
          ~justifyContent=`center,
          ~padding=5.->dp,
          ~margin=12.5->dp,
          ~flexGrow=1.,
          ~height=140.->dp,
          ~flexBasis=42.->pct,
          (),
        ),
      "dna":
        style(
          ~position=`absolute,
          ~top=(-15.)->pct,
          ~right=0.->dp,
          ~bottom=0.->dp,
          ~left=(-20.)->pct,
          ~zIndex=-1,
          ~resizeMode=`cover,
          (),
        ),
    })
  );

let openLink = url => {
  Js.Promise.(
    ReactNative.Linking.openURL(url)
    |> catch(_ => {
         SimpleToast.(
           showWithGravity(
             {j|Você precisa do WhatsApp para entrar em contato. Instale na sua loja de aplicativos|j},
             short,
             bottom,
           )
         );
         resolve();
       })
  );
};

[@react.component]
let make =
    (
      ~navigation,
      ~route:
         ReactNavigation.Core.route(
           Navigators.SubscribeNavigator.StakeParams.params,
         ),
    ) => {
  open ReactNative;
  let cpfCnpj =
    route.params->Belt.Option.mapWithDefault("", param => param.cpfCnpj);
  let query = Query.use(~variables={cpfCnpj: cpfCnpj}, ());
  let user =
    query.userByCpfCnpj
    ->Belt.Option.getWithDefault({name: None, cpfCnpj: ""});
  Js.log(cpfCnpj);
  let name = user.name->Belt.Option.getWithDefault("");
  let cpf = user.cpfCnpj;

  <View style={styles##bg}>
    <ReactNativeSvg.SvgXml
      style={styles##dna}
      width={125.->Style.pct}
      height={125.->Style.pct}
      xml=Svgs.dna
    />
    <View style={styles##container}>
      <View style={styles##top}>
        <ReactNativeSvg.SvgXml
          xml=Svgs.signature
          width={97.->Style.dp}
          height={85.->Style.dp}
        />
        <Text style={styles##orange}>
          {j|ESCRITÓRIO DIGITAL|j}->React.string
        </Text>
      </View>
      <View style={styles##horizontal}>
        <TouchableOpacity
          style={styles##button}
          onPress={_ =>
            openLink("https://www.marcosinacio.adv.br/inteligencia-juridica")
            ->ignore
          }>
          <View>
            <Text style={styles##txt}>
              {j|Conteúdo Jurídico|j}->React.string
            </Text>
          </View>
        </TouchableOpacity>
        <TouchableOpacity
          style={styles##button}
          onPress={_ => {
            let text = {j|Olá! Sou $name, CPF $cpf. Gostaria de falar com um advogado.|j};
            let url = {j|whatsapp://send?text=$text&phone=5583999651707|j};

            openLink(url)->ignore;
          }}>
          <View>
            <Text style={styles##txt}>
              {j|Falar com advogado|j}->React.string
            </Text>
          </View>
        </TouchableOpacity>
        <TouchableOpacity
          style={styles##button}
          onPress={_ => {
            let text = {j|Olá! Sou $name, CPF $cpf. Gostaria de consultar meu processo.|j};
            let url = {j|whatsapp://send?text=$text&phone=5583999651707|j};

            openLink(url)->ignore;
          }}>
          <View>
            <Text style={styles##txt}>
              {j|Consultar meu processo|j}->React.string
            </Text>
          </View>
        </TouchableOpacity>
        <TouchableOpacity
          style={styles##button}
          onPress={_ => {
            let text = {j|Olá! Sou $name, CPF $cpf. Gostaria de falar com uma atendente.|j};
            let url = {j|whatsapp://send?text=$text&phone=5583999651707|j};

            openLink(url)->ignore;
          }}>
          <View>
            <Text style={styles##txt}>
              {j|Falar com atendente|j}->React.string
            </Text>
          </View>
        </TouchableOpacity>
        <TouchableOpacity
          style={styles##button}
          onPress={_ => {
            let text = {j|Olá! Sou $name, CPF $cpf e tenho um amigo que precisa de um advogado.|j};
            let url = {j|whatsapp://send?text=$text&phone=5583999651707|j};

            openLink(url)->ignore;
          }}>
          <View>
            <Text style={styles##txt}>
              {j|Meu amigo precisa de um advogado|j}->React.string
            </Text>
          </View>
        </TouchableOpacity>
        <TouchableOpacity
          style={styles##button}
          onPress={_ =>
            navigation->Navigators.RootNavigator.Navigation.navigate(
              "Contact",
            )
          }>
          <View>
            <Text style={styles##txt}>
              {j|Elogios e críticas|j}->React.string
            </Text>
          </View>
        </TouchableOpacity>
      </View>
    </View>
  </View>;
};