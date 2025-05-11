<script>
  export let skipToMap;
  export let customClass;
</script>

<div 
  on:click={skipToMap}
  class={`z-60 p-4 ml-auto font-mono font-bold text-sm leading-relaxed align-bottom uppercase cursor-pointer text-right ${customClass}`}
>
  Skip To Map
</div>
