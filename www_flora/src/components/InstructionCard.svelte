<!-- Card.svelte -->
<script>
  // Props for the card
  export let illustration = "";
  export let title = "";
  export let roleTitle = "";
  export let roleText = "";
  export let objective = "";
  export let bgColor = "";
  export let onClose = () => {};
</script>

<div class={`fixed inset-0 w-screen h-full ${bgColor} flex flex-col items-center`}>
  <button 
    class="absolute top-4 right-4 hover:opacity-80 transition-opacity z-50"
    on:click={onClose}
  >
    <img 
      src="/assets/buttons/close.png" 
      alt="Close" 
      class="m-4 w-15 h-auto"
    />
  </button>

  <div class="flex flex-col items-center gap-0 overflow-y-auto font-mono">
    <div class="relative w-full">
      <img
        src={illustration}
        alt="il"
        class="w-full h-auto"
      />
    </div>
    <div class="relative w-full">
    <img
      src="/assets/cards/bg.png"
      alt="Card bg"
      class="w-full h-auto"
    />
    <div class="absolute inset-0 w-full h-auto pt-15 pl-8 pr-4">
        <div class="font-bold">💫 Role: {roleTitle}</div>
        <div class="h-[5px]"></div>
        <div>{roleText}</div>
        <div class="h-[40px]"></div>
        <div class="font-bold">🧩 Objective</div>
        <div class="h-[5px]"></div>
        <div>{objective}</div>
    </div>
    </div>
  </div>
</div>
