import { defineConfig } from 'vite'
import react from '@vitejs/plugin-react'

// https://vite.dev/config/
export default defineConfig({
  plugins: [react()],
  server: {
    host: '0.0.0.0',
    port: Number(process.env.PORT) || 4000,
    allowedHosts: [
      'project3-gang22-frontend.onrender.com',  // allow Render host
      'localhost'
    ],
    define: {
    'process.env.NODE_ENV': '"production"'
}
    
  }
})
