[@react.component]
let app = () =>
  <ReasonRelay.Context.Provider environment=Relay.environment>
    <React.Suspense fallback={<Loading />}>
      <Router.RootStackScreen />
    </React.Suspense>
  </ReasonRelay.Context.Provider>;