# React Server Components

- UI development, want a good UX, cheap maintenance and fast perf.
- You want stuff to generally appear at the same time, instead of in random order according to the network responses.
- API response becomes very coupled to my presentation. If I remove some data I have to make sure it's removed from there too.
- Want to be able to make every component responsible for its own data fetching. But this is slow and is beholden to the network waterfall.
- Relay + GraphQL let you have your components be responsible for their own data, but not all apps should have GraphQL backends to be fast.
- Soluton is move the React to the server so they can fetch data really easily and send the response back.
- Server components execute on the backend only, something that will be introduced to React. 
- Server components are a new component that say it will only render on the backend. Adding a `.client` extension to indicate that it's a client. fetch` api works as if its synchronous.
- This component just maps over a lsit of notes and renders it out. No interactivity so it could be a good candidate for a server component. `.server`. Fetch happens on the server so it'll be really fast, much faster than fetching from the client.
- Doing this can remove the cost of needing a bundle, makes it much easier for a user.
- Server components cannot have any interactivity, this has to happen on the client. Fortunately server components can import `client` components for state. Props to client components need to be serializable to JSON, like JSX. JSX gets rendered by the server before it hits the client.
- Server compoennts pass rendered child components. Pass fully rendered JSX. If we look at the page, the sidebar is rendered and we can see that the child component is not passed down in the network.
- SSR is where you take your client side JS and render it into HTML. benefit is your client can see something really quickly. server components are different. It means that the client side state is never blown away. Server components don't go to HTML they render to a special format. SSR and server components are complementary and can be used together. Server components let you preserve the client side state.
- Shared components can render on server or client, depends on what kind of component imports it. In this case, a server component imports it so its rendered on the server. But, we can also import it on the client.
- If the server updates an element, client side state stays which is super cool.
- Suspense and server components work really well together to show something. These don't render to HTML but to a special format. As we get the first part of the server tree we can send that down to the client so it can show the loading state while it's waiting for the rest of the response to come back.


- Server components have zero effect on the bundle size. We can have a server component tht imports some libraries and you can be confident this doesn't get shipped to the user. You have to make decisions about what gets rendered on the client and what stays on the server.
- Server components let you access the backend resources directly, which is safe apparently...
- Server components let you only load the code that is necessary. So if you hide something behind a ternary or something, then this doesn't even get send down to the client, and this happens automatically behind the scenes. 
- Server components let you decide the tradeoff for every concrete use case. Data fetching goes on server, but things with fast input can go on the client. It means that a lot of components can be shared so they can run on both the server and the client.
- Server components provide modern UX with a server-driven mental model. I don't need to think too much about how the client server interaction happens, i can just think about what the output looks like.
- Think of your React app that contains both client and server components, you don't think as much about the client fetching. Makes things a bit simpler.
- You can think of existing React apps as ones that exist entirely of client components. Expect initial adoption through frameworks like NextJS.
- They saw that in an experiment they were able to progressively reduce the bundle size down to 29%